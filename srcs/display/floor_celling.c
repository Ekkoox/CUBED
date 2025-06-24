/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_celling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:37 by dsatge            #+#    #+#             */
/*   Updated: 2025/06/24 15:52:58 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	display_floor_celling(t_cubed cube)
{
	int	x;
	int	y;
	
	x = 0;
	y = 0;
	while (y < 540)
	{
		x = 0;
		while (x < 1920)
		{
			mlx_pixel_put(cube.mlx, cube.win, x, y, 4282009);
			x++;
		}
		y++;
	}
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			mlx_pixel_put(cube.mlx, cube.win, x, y,7030076);
			x++;
		}
		y++;
	}
}
