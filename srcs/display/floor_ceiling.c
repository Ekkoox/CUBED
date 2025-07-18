/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:37 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/18 20:14:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	fill_image_color(char *pix_char, int colour, int width, int height)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			i = y * (WIDTH * 4) + x * (BPP / 8);
			pix_char[i + 0] = color_convert(colour, BLUE);
			pix_char[i + 1] = color_convert(colour, GREEN);
			pix_char[i + 2] = color_convert(colour, RED);
			pix_char[i + 3] = 0;
			x++;
		}
		y++;
	}
}

static int	gener_sky(t_cubed cube, int x, int y)
{
	int		bpp;
	int		width;
	int		endian;
	char	*sky;
	void	*ptr_sky;

	bpp = 32;
	width = WIDTH * 4;
	endian = 0;
	ptr_sky = mlx_new_image(cube.mlx, WIDTH, HEIGHT / 2);
	if (ptr_sky == NULL)
		return (ft_printf(2, "Error: mlx failure\n"), EXIT_FAILURE);
	sky = mlx_get_data_addr(ptr_sky, &bpp, &width, &endian);
	fill_image_color(sky, cube.pixel_data->ceiling_color, WIDTH, HEIGHT / 2);
	mlx_put_image_to_window(cube.mlx, cube.win, ptr_sky, x, y);
	mlx_destroy_image(cube.mlx, ptr_sky);
	return (EXIT_SUCCESS);
}


static int	gener_floor(t_cubed cube, int x, int y)
{
	int		bpp;
	int		width;
	int		endian;
	char	*floor;

	bpp = 32;
	width = WIDTH * 4;
	endian = 0;
	cube.pixel_data->ptr_floor = mlx_new_image(cube.mlx, WIDTH, HEIGHT / 2);
	if (cube.pixel_data->ptr_floor == NULL)
		return (ft_printf(2, "Error: mlx failure\n"), EXIT_FAILURE);
	floor = mlx_get_data_addr(cube.pixel_data->ptr_floor, &bpp, &width, &endian);
	fill_image_color(floor, cube.pixel_data->floor_color, WIDTH, HEIGHT / 2);
	mlx_put_image_to_window(cube.mlx, cube.win, cube.pixel_data->ptr_floor, x, y);
	return (EXIT_SUCCESS);
}

int	display_floor_ceiling(t_cubed cube)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (gener_sky(cube, x, y) == 1)
		return (EXIT_FAILURE);
	y = HEIGHT / 2;
	if (gener_floor(cube, x, y) == 1)
		return (EXIT_FAILURE);
	return (0);
}
