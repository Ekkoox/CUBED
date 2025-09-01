/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/01 17:05:41 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	orientation_color(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL && cube->ray->step_x == 1)
		return (EAST_C);
	else if (cube->ray->dda == VERTICAL && cube->ray->step_x == -1)
		return (WEST_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == 1)
		return (SOUTH_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == -1)
		return (NORTH_C);
	return (0);
}

int	angle_correction(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

void	draw_projection(t_cubed *cube, double perp_dist, int x_start, int x_end)
{
	int	i;
	int	x;
	int	color;
	int	draw_start;
	int	draw_end;

	draw_start = -((int)(HEIGHT / perp_dist)) / 1 + HEIGHT / 2;
	draw_end = ((int)(HEIGHT / perp_dist)) / 1 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	while (draw_start++ <= draw_end)
	{
		x = x_start;
		while (x++ <= x_end)
		{
			i = (draw_start * cube->pixel_data->size_len_background)
				+ (x * (cube->pixel_data->bpp_background / 8));
			color = orientation_color(cube);
			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
			cube->pixel_data->background[i + 2] = color_convert(color, RED);
		}
	}
}

void	pix_projection_column(int screen_x, int ray_width, double perp_dist,
	t_cubed *cube)
{
	int	x_start;
	int	x_end;

	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	x_start = screen_x * ray_width;
	x_end = x_start + ray_width - 1;
	if (x_start < 0)
		x_start = 0;
	if (x_end >= WIDTH)
		x_end = WIDTH - 1;
	draw_projection(cube, perp_dist, x_start, x_end);
}

void	ray_cast(t_cubed *cube, int screen_x)
{
	double	perp_dist;

	dda(cube);
	if (cube->ray->dda == VERTICAL)
		perp_dist = (cube->ray->move_spot_x - cube->ray->player_pos_x
				+ (1.0 - cube->ray->step_x) * 0.5) / cube->ray->ray_rad_x;
	else
		perp_dist = (cube->ray->move_spot_y - cube->ray->player_pos_y
				+ (1.0 - cube->ray->step_y) * 0.5) / cube->ray->ray_rad_y;
	perp_dist = perp_dist * cos(cube->ray->rad - (angle_correction(cube->player->facing_pos)
				* (M_PI / 180.0)));
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	pix_projection_column(screen_x, RAY_PER_PIX, perp_dist, cube);
}

int	ray_vision(t_cubed *cube)
{
	double	fov_rad;
	int		total_rays;
	int		ray;

	fov_rad = (VISION_WIDE * M_PI) / 180.0;
	total_rays = WIDTH * RAY_PER_PIX;
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
		HEIGHT * cube->pixel_data->size_len_background);
	cube->ray = ft_calloc(1, sizeof(t_ray));
	if (!cube->ray)
		return (EXIT_FAILURE);
	ray = -1;
	while (++ray < total_rays)
	{
		cube->ray->rad = (angle_correction(cube->player->facing_pos)
				* (M_PI / 180.0))
			- (fov_rad / 2.0) + (ray * fov_rad) / (double)(total_rays - 1);
		if (ray % RAY_PER_PIX == 0 && (ray / RAY_PER_PIX) < WIDTH)
			ray_cast(cube, ray / RAY_PER_PIX);
	}
	mlx_put_image_to_window(cube->mlx, cube->win,
		cube->pixel_data->ptr_background, 0, 0);
	return (0);
}
