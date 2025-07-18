/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:38:18 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/18 13:15:23 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	next_move_check(t_cubed *cube, int dir, int step)
{
	int	next_position;
	
	next_position = 0;
	if (dir == UP)
	{
	next_position = (cube->pixel_data->play_pix_y - (step)) * cube->pixel_data->size_len
		+ cube->pixel_data->play_pix_x * (cube->pixel_data->bpp / 8);
	}
	else if (dir == DOWN)
	{
	next_position = (cube->pixel_data->play_pix_y + (step * 2)) * cube->pixel_data->size_len
		+ cube->pixel_data->play_pix_x * (cube->pixel_data->bpp / 8);
	}
	else if (dir == LEFT)
	{
	next_position = cube->pixel_data->play_pix_y * cube->pixel_data->size_len
		+ (cube->pixel_data->play_pix_x - (step)) * (cube->pixel_data->bpp / 8);
	}
	else if (dir == RIGHT)
	{
	next_position = cube->pixel_data->play_pix_y * cube->pixel_data->size_len
		+ (cube->pixel_data->play_pix_x + (step * 2)) * (cube->pixel_data->bpp / 8);
	}
	return (next_position);
}

static int	colour_check(t_cubed *cube, int next_pos, int dir)
{
	int	status;
	int	next_pos_aligned;

	status = 0;
	if (dir == UP)
		next_pos_aligned = next_pos + STEP_LEN * (cube->pixel_data->bpp / 8);
	if (dir == DOWN)
		next_pos_aligned = next_pos + STEP_LEN * (cube->pixel_data->bpp / 8);
	if (dir == LEFT)
		next_pos_aligned = next_pos + STEP_LEN * cube->pixel_data->size_len;
	if (dir == RIGHT)
		next_pos_aligned = next_pos + STEP_LEN * cube->pixel_data->size_len;
	if (cube->pixel_data->minimap[next_pos + 0] != color_convert(FLOOR_MAP_C, BLUE) ||
			cube->pixel_data->minimap[next_pos_aligned + 0] != color_convert(FLOOR_MAP_C, BLUE))
		status++;
	if (cube->pixel_data->minimap[next_pos + 1] != color_convert(FLOOR_MAP_C, GREEN) ||
			cube->pixel_data->minimap[next_pos_aligned + 0] != color_convert(FLOOR_MAP_C, BLUE))
		status++;
	if (cube->pixel_data->minimap[next_pos + 2] != color_convert(FLOOR_MAP_C, RED) ||
			cube->pixel_data->minimap[next_pos_aligned + 0] != color_convert(FLOOR_MAP_C, BLUE))
		status++;
	if (status != 0)
		return (1);
	return (0);
}

void	change_pix(t_cubed *cube, int colour)
{
	int	i;
	int tmp_y;
	int tmp_x;
	
	tmp_y = cube->pixel_data->play_pix_y;
	tmp_x = cube->pixel_data->play_pix_x;
	while (tmp_y < cube->pixel_data->play_pix_y + 10)
	{
		tmp_x = cube->pixel_data->play_pix_x;
		while (tmp_x < cube->pixel_data->play_pix_x + 10)
		{
			i = tmp_y * cube->pixel_data->size_len + tmp_x * (cube->pixel_data->bpp / 8);
			cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
			cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
			cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
			cube->pixel_data->minimap[i + 3] = (char) 0;
			tmp_x++;
		}
		tmp_y++;
	}
}

static int	check_path(int dir, t_cubed *cube)
{
	if (dir == UP && colour_check(cube, next_move_check(cube, dir, STEP_LEN), dir) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->pixel_data->play_pix_y = cube->pixel_data->play_pix_y - STEP_LEN;
		change_pix(cube, PLAYER_C);
	}
	if (dir == DOWN && colour_check(cube, next_move_check(cube, dir, STEP_LEN), dir) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->pixel_data->play_pix_y = cube->pixel_data->play_pix_y + STEP_LEN;
		change_pix(cube, PLAYER_C);
	}
	if (dir == LEFT && colour_check(cube, next_move_check(cube, dir, STEP_LEN), dir) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->pixel_data->play_pix_x = cube->pixel_data->play_pix_x - STEP_LEN;
		change_pix(cube, PLAYER_C);
	}
	if (dir == RIGHT && colour_check(cube, next_move_check(cube, dir, STEP_LEN), dir) == 0)
	{	
		change_pix(cube, FLOOR_MAP_C);
		cube->pixel_data->play_pix_x = cube->pixel_data->play_pix_x + STEP_LEN;
		change_pix(cube, PLAYER_C);
	}
	return (0);
}

int	click(int keycode, t_cubed *cube)
{
	if (keycode == KEY_ESC)
	{
		free_tmp(cube);
		exit(0);
	}
	if (keycode == KEY_W)
	{
		check_path(UP, cube);
	}
	if (keycode == KEY_S)
	{
		check_path(DOWN, cube);
	}
	if (keycode == KEY_A)
	{
		check_path(LEFT, cube);
	}
	if (keycode == KEY_D)
	{
		check_path(RIGHT, cube);
	}
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_minimap, 5, 5);
	return (EXIT_SUCCESS);
}
