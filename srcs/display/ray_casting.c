/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/11 15:42:28 by dsatge           ###   ########.fr       */
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
	int		ray;
	int		status;

	status = 0;
	ray = 0;
	ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + (int)pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + (int)pix_x) * (cube->pixel_data->bpp / 8));
	if (cube->pixel_data->minimap[ray + 0] == color_convert(WALL_MAP_C, BLUE))
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

void	pix_projection(double x_init, double resolution, int y, t_cubed *cube)
{
	int	i;
	int	y_max;
	int	x;
	int color;

	y_max = HEIGHT - y;
	while (y < y_max)
	{
		x = x_init;
		while (x < x_init + resolution)
		{
			i = (y * cube->pixel_data->size_len_background) + (x * (cube->pixel_data->bpp_background / 8));
			color = cube->wall_orientation;
			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
			cube->pixel_data->background[i + 2] = color_convert(color, RED);
			x++;
		}
		y++;
	}
}


void	projection(int dist, double rad, t_cubed *cube, int range)
{
	int	x;
	double	x_init;
	int	y;
	double	resolution;
	
	(void) rad;

	resolution = (WIDTH / (double)VISION_WIDE);
	x_init = resolution + (resolution * range);
	x = x_init;
	y = dist;
	// y = cos(rad) * (dist);
	// (void) rad;
	pix_projection(x_init, resolution, y, cube);
}

void	ray_cast(t_cubed *cube, int colour, double rad, int range, double play_angle)
{
	double	pix_x;
	double	pix_y;
	// double	corrected_dist;
	int		dist;

	// dist = PLAYER_SIZE;
	dist = PLAYER_SIZE * cos(rad - play_angle);
	// corrected_dist = dist * cos(rad - play_angle);
	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos + dist) < HEIGHT)
	{
		pix_x = (cos(rad) * (dist));
		pix_y = (sin(rad) * (dist));
		if (ray_check(pix_x, pix_y, cube) == 0)
		{			
			pix_colour((int)pix_x, (int)pix_y, colour, cube);
		}
		else
			break ;
		dist += 1;
	}
	projection(dist, rad, cube, range);
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
	double	rad;
	double	player_angle_rad;
	int		angle;
	int		range;

	range = 0;
	rad = 0;
	player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
	angle = cube->player->facing_pos - 30;
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty, HEIGHT * cube->pixel_data->size_len_background);
	while (angle < cube->player->facing_pos + 30)
	{
		rad = angle_correction(angle) * (M_PI / 180.0);
		ray_cast(cube, colour, rad, range, player_angle_rad);
		angle++;
		range++;
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_background, 0, 0);
}
