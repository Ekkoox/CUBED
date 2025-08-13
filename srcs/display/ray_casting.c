/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/12 18:20:26 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	read_orientation(int orientation, t_cubed *cube)
{
	if (orientation == NORTH)
		return (TEST_N_C);
	if (orientation == SOUTH)
		return (TEST_S_C);
	if (orientation == WEST)
		return (TEST_W_C);
	if (orientation == EAST)
		return (TEST_E_C);
	if (orientation == ANGLE)
		return (cube->prev_color);
	return (cube->prev_color);
}

int	ray_check(double pix_x, double pix_y, t_cubed *cube)
{
	unsigned long		ray;
	int					status;
	unsigned long 		minimap_size;

	status = 0;
	ray = 0;
	minimap_size = HEIGHT * cube->pixel_data->size_len;
	ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + (int)pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + (int)pix_x) * (cube->pixel_data->bpp / 8));
	if (ray < 0 || ray >= minimap_size || !cube->pixel_data->minimap[ray])
		return (1);
	if (cube->pixel_data->minimap[ray] == color_convert(WALL_MAP_C, BLUE))
		status++;
	if (cube->pixel_data->minimap[ray + 1] == color_convert(WALL_MAP_C, GREEN))
		status++;
	if (cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C, RED))
		status++;
	if (status == 3)
	{
		cube->wall_orientation = read_orientation(cube->pixel_data->minimap[ray + 3], cube);
		cube->prev_color = cube->wall_orientation;
		return (1);
	}
	return (0);
}

// void	pix_projection(int x_init, double resolution, int y, t_cubed *cube)
// {
// 	unsigned long	i;
// 	int	y_max;
// 	double	x;
// 	double color;
// 	unsigned long	screen_size;

// 	// y_max = HEIGHT - y;
// 	y_max = (WALL_SCALE * 32) / y;
// 	y = (cube->pixel_data->size_len_background / 2) - (y_max / 2);
// 	screen_size = HEIGHT * cube->pixel_data->size_len_background;
// 	while (y < y_max)
// 	{
// 		x = ceil(x_init);
// 		while (x <= floor(x_init + resolution))
// 		{
// 			i = (y * cube->pixel_data->size_len_background) + (x * (cube->pixel_data->bpp_background / 8));
// 			if (i < 0 || i > screen_size || !cube->pixel_data->background[i])
// 			{
// 				x++;
// 				break ;
// 			}	
// 			color = cube->wall_orientation;
// 			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
// 			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
// 			cube->pixel_data->background[i + 2] = color_convert(color, RED);
// 			x++;
// 		}
// 		y ++;
// 	}
// }

void draw_column(int x_start, int width, int wall_height, int color, t_cubed *cube)
{
    int x, y;
    int y_start = (HEIGHT / 2) - (wall_height / 2);
    if (y_start < 0) y_start = 0;
    if (y_start + wall_height > HEIGHT) wall_height = HEIGHT - y_start;

    for (y = y_start; y < y_start + wall_height; ++y)
    {
        for (x = x_start; x < x_start + width; ++x)
        {
            unsigned long i = (unsigned long)y * cube->pixel_data->size_len_background
                             + (unsigned long)x * (cube->pixel_data->bpp_background / 8);
            if (i + 2 >= (unsigned long)HEIGHT * cube->pixel_data->size_len_background) continue;
            cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
            cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
            cube->pixel_data->background[i + 2] = color_convert(color, RED);
        }
    }
}


// void	projection(int dist, double ray_angle, t_cubed *cube, int range)
// {
// 	int	x;
// 	double	x_init;
// 	double	y;
// 	double	resolution;
	
// 	resolution = ((double)WIDTH / (double)VISION_WIDE);
// 	x_init = (int)round(resolution * range);
// 	x = x_init;
// 	y = dist * cos(angle_correction(ray_angle - cube->player->facing_pos) * (M_PI / 180.0));
// 	pix_projection(x_init, resolution, y, cube);
// }

void projection(int dist, double ray_angle_rad, t_cubed *cube, int range, double player_angle_rad)
{
    double resolution;
    int x_init;
    int col_width;

	
	resolution = (double)WIDTH / (double)VISION_WIDE;
	x_init = (int)floor(resolution * range); /* départ de la colonne */
	col_width = (int)ceil(resolution); /* largeur en pixels de la colonne */

    /* fish-eye correction : dist_corr = dist * cos(delta_angle) */
    double delta = ray_angle_rad - player_angle_rad;
    double dist_corr = (double)dist * cos(delta);

    if (dist_corr <= 0.0001) dist_corr = 0.0001; /* protection */

    /* SCALE : règle le rendu. Ajuste pour obtenir la taille souhaitée.
       Voici un choix simple : plus dist_corr petit => colonne haute.
       On peut prendre SCALE = HEIGHT * 64 (ou STEP_LEN) ; tester/ajuster. */
    double SCALE = (double)HEIGHT * 32.0; /* ajuste 32.0 selon tes tests */
    int wall_height = (int)(SCALE / dist_corr);

    /* clamp */
    if (wall_height > HEIGHT) wall_height = HEIGHT;

    draw_column(x_init, col_width, wall_height, cube->wall_orientation, cube);
}

// void	ray_cast(t_cubed *cube, int colour, double ray_angle, int range)
// {
// 	double	pix_x;
// 	double	pix_y;
// 	int		dist;

// 	dist = PLAYER_SIZE;
// 	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos + dist) < HEIGHT)
// 	{
// 		pix_x = (cos(ray_angle  * (M_PI / 180.0))) * (dist);
// 		pix_y = (sin(ray_angle * (M_PI / 180.0))) * (dist);
// 		if (ray_check(pix_x, pix_y, cube) == 0)
// 		{			
// 			pix_colour((int)pix_x, (int)pix_y, colour, cube);
// 		}
// 		else
// 			break ;
// 		dist += 1;
// 	}
// 	projection(dist, ray_angle, cube, range);
// }

void ray_cast(t_cubed *cube, int colour, double ray_angle_rad, int range, double player_angle_rad)
{
	double	pix_x;
	double	pix_y;
	int dist;
	
	dist = PLAYER_SIZE;
	while ((cube->player->y_pos + dist) < HEIGHT && (cube->player->x_pos + dist) < WIDTH)
	{
		pix_x = cos(ray_angle_rad) * dist;
		pix_y = sin(ray_angle_rad) * dist;

		if (ray_check(pix_x, pix_y, cube) == 0)
		{
			pix_colour((int)pix_x, (int)pix_y, colour, cube);
		}
		else
			break;
		dist++;
	}
	projection(dist, ray_angle_rad, cube, range, player_angle_rad);
}

int	angle_correction(int angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

void	ray_vision(t_cubed *cube, int colour)
{
	int range;
	int start_angle;
	double player_angle_rad;
	double ray_angle_rad;
	int current_deg;
	
	range = 0;
	start_angle = angle_correction(cube->player->facing_pos - 30);
	player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
			HEIGHT * cube->pixel_data->size_len_background);
	while (range < VISION_WIDE)
	{
		current_deg = angle_correction(start_angle + range);
		ray_angle_rad = current_deg * (M_PI / 180.0);
		ray_cast(cube, colour, ray_angle_rad, range, player_angle_rad);
		range++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_background, 0, 0);
}
