/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/25 15:38:20 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + (int)pix_y)
			* cube->pixel_data->size_len) + ((int)(cube->player->x_pos
				+ (PLAYER_SIZE / 2) + (int)pix_x) * (cube->pixel_data->bpp
				/ 8));
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
		cube->wall_orientation = read_orientation(cube->pixel_data->minimap[ray
				+ 3], cube);
		cube->prev_color = cube->wall_orientation;
		return (1);
	}
	return (0);
}

void    pix_projection(double x_init, double resolution, int y, t_cubed *cube)
{
    int    i;
    int    y_max;
    int    x;
    int    color;

    y_max = HEIGHT - y;
    while (y < y_max)
    {
        x = x_init;
        while (x < x_init + resolution)
        {
            i = (y * cube->pixel_data->size_len_background) + (x
                    * (cube->pixel_data->bpp_background / 8));
            color = cube->wall_orientation;
            cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
            cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
            cube->pixel_data->background[i + 2] = color_convert(color, RED);
            x++;
        }
        y++;
    }
}

// void draw_column(int x_start, int width, int wall_height, int color, t_cubed *cube)
// {
// 	int	i;
// 	int	y_max;
// 	int	x;
// 	int	color;

// 	y_max = HEIGHT - y;
// 	while (y < y_max)
// 	{
// 		x = x_init;
// 		while (x < x_init + resolution)
// 		{
// 			i = (y * cube->pixel_data->size_len_background) + (x
// 					* (cube->pixel_data->bpp_background / 8));
// 			color = cube->wall_orientation;
// 			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
// 			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
// 			cube->pixel_data->background[i + 2] = color_convert(color, RED);
// 			x++;
//         }
// 		++y;
//     }
// }

// void	projection(int dist, double rad, t_cubed *cube, int range)
// {
// 	int		x;
// 	double	x_init;
// 	int		y;
// 	double	resolution;

// 	(void)rad;
// 	resolution = (WIDTH / (double)VISION_WIDE);
// 	// x_init = resolution + (resolution * range);
// 	x_init =(resolution * range);//siuuu
// 	x = x_init;
// 	y = dist;
// 	// y = cos(rad) * (dist);
// 	// (void) rad;
// 	pix_projection(x_init, resolution, y, cube);
// }

// siuuuuuu test ITERER sur la taille de la fenetre au lieu de la fov
void    projection(int dist, double rad, t_cubed *cube, int x_pos)
{
    int     x;
    int     y;
    double  resolution;

    (void)rad;
    resolution = 1; // Chaque rayon correspond à 1 pixel de large
    x = x_pos;     // Position x directe dans la fenêtre
    y = dist;
    pix_projection(x, resolution, y, cube);
}

// void	ray_cast(t_cubed *cube, int colour, double rad, int range,
// 		double play_angle)
// {
// 	double	pix_x;
// 	double	pix_y;
// 	int		dist;

// 	// double	corrected_dist;
// 	// dist = PLAYER_SIZE;
// 	dist = PLAYER_SIZE * cos(rad - play_angle);
// 	// corrected_dist = dist * cos(rad - play_angle);
// 	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos
// 			+ dist) < HEIGHT)
// 	{
// 		pix_x = (cos(rad) * (dist));
// 		pix_y = (sin(rad) * (dist));
// 		if (ray_check(pix_x, pix_y, cube) == 0)
// 		{
// 			pix_colour((int)pix_x, (int)pix_y, colour, cube);
// 		}
// 		else
// 			break ;
// 		dist += 1;
// 	}
// 	projection(dist, rad, cube, range);
// }


// siuuuu test regler le fish eye
void ray_cast(t_cubed *cube, int colour, double rad, int range, double play_angle)
{
    double  pix_x;
    double  pix_y;
    int     dist;
    double  corrected_dist;

    dist = PLAYER_SIZE;
    while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos + dist) < HEIGHT)
    {
        pix_x = (cos(rad) * (dist));
        pix_y = (sin(rad) * (dist));
        if (ray_check(pix_x, pix_y, cube) == 0)
        {
            pix_colour((int)pix_x, (int)pix_y, colour, cube);
        }
        else
        {
            // Correction fish-eye en utilisant la distance perpendiculaire au plan de la caméra
            corrected_dist = dist * cos(rad - play_angle);
            projection(corrected_dist, rad, cube, range);
            break;
        }
        dist += 1;
    }
}

int	angle_correction(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

// void	ray_vision(t_cubed *cube, int colour)
// {
// 	double	rad;
// 	double	player_angle_rad;
// 	int		angle;
// 	int		range;

// 	range = 0;
// 	rad = 0;
// 	player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI
// 			/ 180.0);
// 	angle = cube->player->facing_pos - 45;//siuuu avant 30
// 	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
// 		HEIGHT * cube->pixel_data->size_len_background);
// 	while (angle < cube->player->facing_pos + 45)//siuuu avant 30
// 	{
// 		rad = angle_correction(angle) * (M_PI / 180.0);
// 		ray_cast(cube, colour, rad, range, player_angle_rad);
// 		angle++;
// 		range++;
// 	}
// 	mlx_put_image_to_window(cube->mlx, cube->win,
// 		cube->pixel_data->ptr_background, 0, 0);
// }

// siuuuuuu test ITERER sur la taille de la fenetre au lieu de la fov
void ray_vision(t_cubed *cube, int colour)
{
    double  rad;
    double  player_angle_rad;
    double  ray_angle;
    int     x;
    double  fov_rad;
    
    player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
    fov_rad = (VISION_WIDE * M_PI) / 180.0;  // Conversion FOV en radians
    
    ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
        HEIGHT * cube->pixel_data->size_len_background);
    
    for (x = 0; x < WIDTH; x++)
    {
        // Calcul uniforme de l'angle pour chaque rayon
        ray_angle = player_angle_rad - (fov_rad / 2) + (x * fov_rad) / (WIDTH - 1);
        rad = ray_angle;
        ray_cast(cube, colour, rad, x, player_angle_rad);
    }
    
    mlx_put_image_to_window(cube->mlx, cube->win,
        cube->pixel_data->ptr_background, 0, 0);
}

