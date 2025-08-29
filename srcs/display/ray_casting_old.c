/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_old.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/29 18:47:33 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda(t_cubed *cube)
{
	double	player_pos_x;
	double	player_pos_y;
	double	ray_rad_x;
	double	ray_rad_y;
	int		move_spot_x;
	int		move_spot_y;
	double		delta_x;
	double		delta_y;
	double	dist_line_x;
	double	dist_line_y;
	int		step_x;
	int		step_y;
	int		hit;

	player_pos_x = cube->player->x_pos / BLOC_LEN;
	player_pos_y = cube->player->y_pos / BLOC_LEN;
	ray_rad_x = cos(cube->ray->rad);
	ray_rad_y = sin(cube->ray->rad);
	move_spot_x = player_pos_x;
	move_spot_y = player_pos_y;
	delta_x = fabs(1.0 / ray_rad_x);
	delta_y = fabs(1.0 / ray_rad_y);
	if (ray_rad_x > 0)
	{
		dist_line_x = (move_spot_x + 1.0 - player_pos_x) * delta_x;
		step_x = 1;
	}
	else
	{
		dist_line_x = (player_pos_x - move_spot_x) * delta_x;
		step_x = -1;
	}
	if (ray_rad_y > 0)
	{
		dist_line_y = (move_spot_y + 1.0 - player_pos_y) * delta_y;
		step_y = 1;
	}
	else
	{
		dist_line_y = (player_pos_y - move_spot_y) * delta_y;
		step_y = -1;
	}
	hit = 0;
	while (hit == 0)
	{
		if (dist_line_x < dist_line_y)
		{
			dist_line_x += delta_x;
			move_spot_x += step_x;
			cube->ray->dda = VERTICAL;
		}
		else
		{
			dist_line_y += delta_y;
			move_spot_y += step_y;
			cube->ray->dda = HORIZONTAL;		
		}
		if (cube->map_formated[move_spot_y][move_spot_x] == '1')
			hit = 1;
	}
}

int	check_angle(t_cubed *cube, int orientation)
{
	dda(cube);
	if (orientation == NORTH_WEST)
	{
		if (cube->ray->dda == HORIZONTAL)
			return (SOUTH_C);
		return (EAST_C);
	}
	if (orientation == NORTH_EAST)
	{
		if (cube->ray->dda == HORIZONTAL)
			return (NORTH_C);
		return (EAST_C);
	}
	if (orientation == SOUTH_WEST)
	{
		if (cube->ray->dda == HORIZONTAL)
			return (SOUTH_C);
		return (WEST_C);
	}
	if (orientation == SOUTH_EAST)
	{
		if (cube->ray->dda == HORIZONTAL)
			return (NORTH_C);
		return (WEST_C);
	}
	return (0);
}

int	read_orientation(int orientation, t_cubed *cube)
{
	if (orientation == NORTH)
		return (NORTH_C);
	if (orientation == SOUTH)
		return (SOUTH_C);
	if (orientation == WEST)
		return (WEST_C);
	if (orientation == EAST)
		return (EAST_C);
	if (orientation == 	NORTH_WEST || orientation == NORTH_EAST 
		|| orientation == SOUTH_WEST || orientation == SOUTH_EAST)
		return (check_angle(cube, orientation));
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

void    projection(int dist, double rad, t_cubed *cube, int x_pos)
{
    int     x;
    int     y;
    double  resolution;

    cube->ray->rad = rad;
    resolution = 1; // Chaque rayon correspond à 1 pixel de large
    x = x_pos;     // Position x directe dans la fenêtre
    y = dist;
    pix_projection(x, resolution, y, cube);
}

void ray_cast(t_cubed *cube, double rad, int range, double play_angle)
{
	double	pix_x;
	double	pix_y;
	int	 	dist;
	double	corrected_dist;

	dist = PLAYER_SIZE;
	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos + dist) < HEIGHT)
	{
		pix_x = (cos(rad) * (dist));
		pix_y = (sin(rad) * (dist));
		if (ray_check(pix_x, pix_y, cube) == 0)
		{
			pix_colour((int)pix_x, (int)pix_y, SPARE_C, cube);
		}
		else
		{
			corrected_dist = dist * cos(rad - play_angle);
			cube->ray->x_hit = (cube->player->x_pos + pix_x) / BLOC_LEN;
			cube->ray->y_hit = (cube->player->y_pos + pix_y) / BLOC_LEN;
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

