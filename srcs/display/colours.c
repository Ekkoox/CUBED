/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:51 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/15 22:59:38 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3D.h>
int	color_convert(int colour, int name_colour)
{
	int	res;
	if (name_colour == RED)
	{
		res = colour >> 16 & 0xFF;
	}
	if (name_colour == GREEN)
		res = colour >> 8 & 0xFF;
	if (name_colour == BLUE)
		res = colour & 0xFF;
	return (res);
}

void	wall_colour(int x, int y, t_cubed *cube, int bpp, int size_len)
{
	int	colour;
	int	i;
	int tmp_y;
	int tmp_x;
	
	colour = 9076325;
	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * size_len + tmp_x * (bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
			cube->pixel_data->minimap[i + 3] = (char) 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

void	walk_colour(int x, int y, t_cubed *cube, int bpp, int size_len)
{
	int	colour;
	int	i;
    int tmp_y;
    int tmp_x;

	colour = 11183506;
	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * size_len + tmp_x * (bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
			cube->pixel_data->minimap[i + 3] = 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

void	player_colour(int x, int y, t_cubed *cube, int bpp, int size_len)
{
	int	colour;
	int	i;
	int tmp_y;
	int tmp_x;

	colour = 14176079;
	cube->pixel_data->play_pix_x = x;
	cube->pixel_data->play_pix_y = y;
	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * size_len + tmp_x * (bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
			cube->pixel_data->minimap[i + 3] = 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

// void	wall_colour(char *pix_char, int x, int y, t_cubed *cube, int bpp, int size_len)
// {
// 	int	colour;
// 	int	i;

// 	(void) cube;
// 	colour = 9076325;
// 	i = y * size_len + x * (bpp / 8);
// 	pix_char[i + 0] = color_convert(colour, BLUE);
// 	pix_char[i + 1] = color_convert(colour, GREEN);
// 	pix_char[i + 2] = color_convert(colour, RED);
// 	pix_char[i + 3] = 0;
// }

// void	walk_colour(char *pix_char, int x, int y, t_cubed *cube, int bpp, int size_len)
// {
// 	int	colour;
// 	int	i;

// 	(void) cube;
// 	colour = 11183506;
// 	i = y * size_len + x * (bpp / 8);
// 	pix_char[i + 0] = color_convert(colour, BLUE);
// 	pix_char[i + 1] = color_convert(colour, GREEN);
// 	pix_char[i + 2] = color_convert(colour, RED);
// 	pix_char[i + 3] = 0;

// }

// void	player_colour(char *pix_char, int x, int y, t_cubed *cube, int bpp, int size_len)
// {
// 	int	colour;
// 	int	i;

// 	(void) cube;
// 	colour = 14176079;;
// 	i = y * size_len + x * (bpp / 8);
// 	pix_char[i + 0] = color_convert(colour, BLUE);
// 	pix_char[i + 1] = color_convert(colour, GREEN);
// 	pix_char[i + 2] = color_convert(colour, RED);
// 	pix_char[i + 3] = 0;
// }