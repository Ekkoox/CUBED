/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/02 18:22:20 by dsatge           ###   ########.fr       */
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

int	get_texture_pixel(char *texture, int tex_x, int tex_y, int tex_width)
{
	int	pixel_index;

	if (tex_x < 0 || tex_x >= tex_width || tex_y < 0 || tex_y >= 64)
		return (0);
	pixel_index = (tex_y * tex_width + tex_x) * 4;
	return (*(int *)(texture + pixel_index));
}

char	*get_wall_texture(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL)
	{
		
		return ((cube->ray->step_x == 1) ? cube->imgs->east_texture : cube->imgs->west_texture);
	}
	else
	{
		
	}
	return ((cube->ray->step_y == 1) ? cube->imgs->south_texture : cube->imgs->north_texture);
}

void	draw_textured_wall(t_cubed *cube, int draw_start, int draw_end,
		int x_start, int x_end, double wall_hit, int wall_height)
{
	char	*texture;
	int		tex_x;
	int		tex_y;
	int		i;
	int		color;
	double	tex_step;
	double	tex_pos;
	int		line_offset;
	int		bytes_per_pixel;
	int		size_line;

	int x, y;
	texture = get_wall_texture(cube);
	if (!texture)
		return ;
	tex_x = (int)(wall_hit * 64);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= 64)
		tex_x = 63;
	tex_step = 64.0 / wall_height;
	tex_pos = (draw_start - (-wall_height + HEIGHT) / 2) * tex_step;
	bytes_per_pixel = cube->pixel_data->bpp_background / 8;
	size_line = cube->pixel_data->size_len_background;
	for (y = draw_start; y <= draw_end; y++)
	{
		tex_y = (int)tex_pos;
		if (tex_y >= 64)
			tex_y = 63;
		color = get_texture_pixel(texture, tex_x, tex_y, 64);
		line_offset = y * size_line;
		for (x = x_start; x <= x_end; x++)
		{
			i = line_offset + (x * bytes_per_pixel);
			*(int *)(cube->pixel_data->background + i) = color;
		}
		tex_pos += tex_step;
	}
}


void	draw_projection(t_cubed *cube, double perp_dist, int x_start, int x_end)
{
	int		draw_start;
	int		draw_end;
	int		wall_height;
	double	wall_hit;

	wall_height = (int)(HEIGHT / perp_dist);
	draw_start = (-wall_height + HEIGHT) / 2;
	draw_end = (wall_height + HEIGHT) / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (cube->ray->dda == VERTICAL)
		wall_hit = cube->ray->player_pos_y + perp_dist * cube->ray->ray_rad_y;
	else
		wall_hit = cube->ray->player_pos_x + perp_dist * cube->ray->ray_rad_x;
	wall_hit -= floor(wall_hit);
	draw_textured_wall(cube, draw_start, draw_end, x_start, x_end, wall_hit,
		wall_height);
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
		perp_dist = (cube->ray->move_spot_x - cube->ray->player_pos_x + (1.0
					- cube->ray->step_x) * 0.5) / cube->ray->ray_rad_x;
	else
		perp_dist = (cube->ray->move_spot_y - cube->ray->player_pos_y + (1.0
					- cube->ray->step_y) * 0.5) / cube->ray->ray_rad_y;
	if (cube->ray->dda == VERTICAL)
		perp_dist = cube->ray->dist_line_x - cube->ray->delta_x;
	if (cube->ray->dda == HORIZONTAL)
		perp_dist = cube->ray->dist_line_y - cube->ray->delta_y;
	perp_dist = perp_dist * cos(cube->ray->rad
			- (angle_correction(cube->player->facing_pos) * (M_PI / 180.0)));
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	pix_projection_column(screen_x, RAY_PER_PIX, perp_dist, cube);
}

int	ray_vision(t_cubed *cube)
{
	double	fov_rad;
	int		ray;
	double	angle_step;
	double	base_angle;

	fov_rad = (VISION_WIDE * M_PI) / 180.0;
	angle_step = fov_rad / (double)(WIDTH - 1);
	base_angle = (angle_correction(cube->player->facing_pos) * (M_PI / 180.0))
		- (fov_rad / 2.0);
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
		HEIGHT * cube->pixel_data->size_len_background);
	cube->ray = ft_calloc(1, sizeof(t_ray));
	if (!cube->ray)
		return (EXIT_FAILURE);
	ray = -1;
	while (++ray < WIDTH)
	{
		cube->ray->rad = base_angle + (ray * angle_step);
		if (ray % RAY_PER_PIX == 0)
			ray_cast(cube, ray / RAY_PER_PIX);
	}
	mlx_put_image_to_window(cube->mlx, cube->win,
		cube->pixel_data->ptr_background, 0, 0);
	return (0);
}
