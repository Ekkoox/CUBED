/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/29 22:04:48 by dsatge           ###   ########.fr       */
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

void    pix_projection(double x_init, double resolution, double y, t_cubed *cube)
{
    int    i;
    int    x;
    int    color;

	if (y < 1e-6)
		y = 1e-6;
	int line_height = (int)(HEIGHT / y);
	int draw_start = -line_height / 2 + HEIGHT / 2;
	int draw_end   =  line_height / 2 + HEIGHT / 2;

	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
    while (draw_start < draw_end)
    {
        x = x_init;
        while (x < x_init + resolution)
        {
            i = (draw_start * cube->pixel_data->size_len_background) + (x
                    * (cube->pixel_data->bpp_background / 8));
			color = orientation_color(cube);
            cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
            cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
            cube->pixel_data->background[i + 2] = color_convert(color, RED);
            x++;
        }
        // y++;
		draw_start++;
    }
}

void    projection(double dist, double rad, t_cubed *cube, int x_pos)
{
    int     x;
    int     y;
    double  resolution;

	(void) rad;
    resolution = 1; // Chaque rayon correspond à 1 pixel de large
    x = x_pos;     // Position x directe dans la fenêtre
    y = dist;
    pix_projection(x, resolution, y, cube);
}

void ray_cast(t_cubed *cube, double rad, int range, double play_angle)
{
	// int	 	dist;
	double	corr_dist_x;
	double	corr_dist_y;
	// double	corr_dist;
	double	perp_dist;

	(void)play_angle;
	cube->ray->rad = rad;
	dda(cube);
	corr_dist_x = cube->ray->x_hit - cube->ray->player_pos_x;
	corr_dist_y = cube->ray->y_hit - cube->ray->player_pos_y;
	if (cube->ray->dda == VERTICAL)
		perp_dist = (cube->ray->move_spot_x - cube->ray->player_pos_x
					+ (1.0 - cube->ray->step_x) * 0.5) / cube->ray->ray_rad_x;
	else
		perp_dist = (cube->ray->move_spot_y - cube->ray->player_pos_y
					+ (1.0 - cube->ray->step_y) * 0.5) / cube->ray->ray_rad_y;
	// dist = sqrt((corr_dist_x * corr_dist_x) + (corr_dist_y * corr_dist_y));
	// corr_dist = dist * cos(rad - play_angle);
	projection(perp_dist, rad, cube, range);
}

int	angle_correction(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

int	ray_vision(t_cubed *cube)
{
	double	player_angle_rad;
	double	ray_angle;
	int		x;
	double	fov_rad;
		
	player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
	fov_rad = (VISION_WIDE * M_PI) / 180.0;  // Conversion FOV en radians
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
		HEIGHT * cube->pixel_data->size_len_background);
	cube->ray = ft_calloc(sizeof(t_ray), sizeof(t_ray));
	if (!cube->ray)
		return (EXIT_FAILURE);
	x = -1;
	while (x++ < WIDTH)
	{
		ray_angle = player_angle_rad - (fov_rad / 2) + (x * fov_rad) / (WIDTH - 1);
		ray_cast(cube, ray_angle, x, player_angle_rad);
	}
	mlx_put_image_to_window(cube->mlx, cube->win,
		cube->pixel_data->ptr_background, 0, 0);
	return (0);
}

