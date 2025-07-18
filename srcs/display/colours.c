/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 17:22:51 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/18 15:06:07 by dsatge           ###   ########.fr       */
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

void	wall_colour(int x, int y, t_cubed *cube)
{
	int	i;
	int tmp_y;
	int tmp_x;
	
	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x * (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(WALL_MAP_C, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(WALL_MAP_C, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(WALL_MAP_C, RED);
			cube->pixel_data->minimap[i + 3] = (char) 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

void	walk_colour(int x, int y, t_cubed *cube)
{
	int	i;
    int tmp_y;
    int tmp_x;

	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x * (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(FLOOR_MAP_C, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(FLOOR_MAP_C, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(FLOOR_MAP_C, RED);
			cube->pixel_data->minimap[i + 3] = 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

void	player_colour(int x, int y, t_cubed *cube)
{
	int	i;
	int tmp_y;
	int tmp_x;

	cube->pixel_data->play_pix_x = x;
	cube->pixel_data->play_pix_y = y;
	tmp_y = y;
	tmp_x = x;
	while (tmp_y < y + 10)
	{
		tmp_x = x;
		while (tmp_x < x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x * (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(PLAYER_C, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(PLAYER_C, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(PLAYER_C, RED);
			cube->pixel_data->minimap[i + 3] = 0;
			tmp_x++;
		}
		tmp_y++;
	}
}
