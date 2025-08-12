/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/12 15:14:14 by dsatge           ###   ########.fr       */
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

void	pix_projection(int x_init, double resolution, int y, t_cubed *cube)
{
	unsigned long	i;
	int	y_max;
	double	x;
	double color;
	unsigned long	screen_size;

	y_max = HEIGHT - y;
	screen_size = HEIGHT * cube->pixel_data->size_len_background;
	while (y < y_max)
	{
		x = ceil(x_init);
		while (x <= floor(x_init + resolution))
		{
			i = (y * cube->pixel_data->size_len_background) + (x * (cube->pixel_data->bpp_background / 8));
			if (i < 0 || i > screen_size || !cube->pixel_data->background[i])
			{
				x++;
				break ;
			}	
			color = cube->wall_orientation;
			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
			cube->pixel_data->background[i + 2] = color_convert(color, RED);
			x++;
		}
		y ++;
	}
}


void	projection(int dist, double ray_angle, t_cubed *cube, int range)
{
	int	x;
	double	x_init;
	double	y;
	double	resolution;
	
	resolution = ((double)WIDTH / (double)VISION_WIDE);
	x_init = (int)round(resolution * range);
	x = x_init;
	y = dist;
	y = cos(ray_angle * (M_PI / 180.0)) * (dist);
	pix_projection(x_init, resolution, y, cube);
}

void	ray_cast(t_cubed *cube, int colour, double angle, int range)
{
	double	pix_x;
	double	pix_y;
	int		dist;

	dist = PLAYER_SIZE;
	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos + dist) < HEIGHT)
	{
		pix_x = (cos(angle  * (M_PI / 180.0))) * (dist);
		pix_y = (sin(angle * (M_PI / 180.0))) * (dist);
		if (ray_check(pix_x, pix_y, cube) == 0)
		{			
			pix_colour((int)pix_x, (int)pix_y, colour, cube);
		}
		else
			break ;
		dist += 1;
	}
	projection(dist, angle, cube, range);
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
	int		angle;
	int		range;

	range = 0;
	// player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
	angle = angle_correction(cube->player->facing_pos - 30);
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty, HEIGHT * cube->pixel_data->size_len_background);
	while (range < VISION_WIDE)
	{
		ray_cast(cube, colour, angle, range);
		angle++;
		range++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_background, 0, 0);
}
