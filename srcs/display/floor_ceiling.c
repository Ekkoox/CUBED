/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 15:46:37 by dsatge            #+#    #+#             */
/*   Updated: 2025/06/25 18:52:38 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	color_convert(int colour, int name_colour)
{
	int	res;

	if (name_colour == RED)
		res = colour >> 16 & 0xFF;
	if (name_colour == GREEN)
		res = colour >> 8 & 0xFF;
	if (name_colour == BLUE)
		res = colour & 0xFF;
	return (res);
}

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

int	display_floor_ceiling(t_cubed cube)
{
	int	x;
	int	y;
	int	bpp = 32;
	int width = (WIDTH * 4);
	int	endian = 0;
	
	x = 0;
	y = 0;
	// sky
	void *img_ptr = mlx_new_image(cube.mlx, WIDTH, HEIGHT / 2);
	if (img_ptr == NULL)
		return (ft_printf(2, "ca na pas marche\n"), EXIT_FAILURE);
	// mlx_pixel_put(cube.mlx, cube.win, x, y, 4282009);
	char *my_img_data = mlx_get_data_addr(img_ptr, &bpp, &width, &endian);
	fill_image_color(my_img_data, 4282009, WIDTH, HEIGHT / 2);
	mlx_put_image_to_window(cube.mlx, cube.win, img_ptr, x, y);
	// floor
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(cube.mlx, cube.win, x, y, 7030076);
			x++;
		}
		y++;
	}
	return (0);
}



