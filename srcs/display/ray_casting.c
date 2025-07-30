/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/30 19:17:40 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	ray_check(double pix_x, double pix_y, t_cubed *cube)
{
	int		ray;

	ray = 0;
	ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + (int)pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + (int)pix_x) * (cube->pixel_data->bpp / 8));
	if (cube->pixel_data->minimap[ray + 0] == color_convert(WALL_MAP_C, BLUE))
		return (1);
	if (cube->pixel_data->minimap[ray + 1] == color_convert(WALL_MAP_C, GREEN))
		return (1);
	if (cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C, RED))
		return (1);
	return (0);
}

void	pix_projection(int x, int y, int colour, t_cubed *cube)
{
	int	i;
	
	i = (y * cube->pixel_data->size_len_background) + (x * (cube->pixel_data->bpp_background / 8));
	cube->pixel_data->background[i + 0] = color_convert(colour, BLUE);
	cube->pixel_data->background[i + 1] = color_convert(colour, GREEN);
	cube->pixel_data->background[i + 2] = color_convert(colour, RED);
	cube->pixel_data->background[i + 3] = (char) 0;
}


void	projection(int dist, double rad, t_cubed *cube)
{
	int	x;
	int	y;
	
	x = (WIDTH / 2) - 20;
	y = (dist);
	(void) rad;
	while (y <= (HEIGHT - dist))
	{
		x = (WIDTH / 2) - 20;
		while (x < (WIDTH / 2) + 20)
		{
			pix_projection(x, y, TEST_C, cube);
			x++;
		}
		y++;
	}
}

void	ray_vision(t_cubed *cube, int colour)
{
	double	rad;
	double	pix_x;
	double	pix_y;
	int		dist;

	dist = PLAYER_SIZE;
	rad = cube->player->facing_pos * (M_PI / 180.0);
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
	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty, HEIGHT * cube->pixel_data->size_len_background);
	projection(dist, rad, cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_background, 0, 0);
}
