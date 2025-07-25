/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:38:18 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/25 19:17:53 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	colour_check(t_cubed *cube, int next_pos, int dir)
{
	int	status;

	status = 0;
	(void) dir;
	(void) next_pos;
	(void) cube;
	// if (cube->pixel_data->minimap[next_pos + 0] != color_convert(FLOOR_MAP_C, BLUE))
	// 	status++;
	// if (cube->pixel_data->minimap[next_pos + 1] != color_convert(FLOOR_MAP_C, GREEN))
	// 	status++;
	// if (cube->pixel_data->minimap[next_pos + 2] != color_convert(FLOOR_MAP_C, RED))
	// 	status++;
	// if (status != 0)
	// 	return (1);
	return (0);
}

void	change_pix(t_cubed *cube, int colour)
{
	int	i;
	int tmp_y;
	int tmp_x;
	
	tmp_y = (int)cube->player->y_pos;
	tmp_x = (int)cube->player->x_pos;
	while (tmp_y < cube->player->y_pos + 10)
	{
		tmp_x = (int)cube->player->x_pos;
		while (tmp_x < cube->player->x_pos + 10)
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

void move_player_forward(t_cubed *cube)
{
	double		rad;
	double		pix_x;
	double		pix_y;
	int		next_position;
	
	rad = cube->player->facing_pos * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	next_position = ((int)(cube->player->y_pos + pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + pix_x) * (cube->pixel_data->bpp / 8));
	if (colour_check(cube, next_position, KEY_W) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}

void move_player_backward(t_cubed *cube)
{
	double		rad;
	double		angle;
	int			next_position;
	double		pix_x;
	double		pix_y;

	angle = (cube->player->facing_pos - 180);
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	rad = angle * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	next_position = ((int)(cube->player->y_pos + pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + pix_x) * (cube->pixel_data->bpp / 8));
	if (colour_check(cube, next_position, KEY_S) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}

void move_player_side(t_cubed *cube, int dir)
{
	double		rad;
	double		angle;
	double		pix_y;
	double		pix_x;
	int			next_position;
	
	if (dir == KEY_A)
		angle = cube->player->facing_pos - 90;
	if (dir == KEY_D)
		angle = cube->player->facing_pos + 90;
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
	rad = angle * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	next_position = ((int)(cube->player->y_pos + pix_y) * cube->pixel_data->size_len)
		+ ((int)(cube->player->x_pos + pix_x) * (cube->pixel_data->bpp / 8));
	if (colour_check(cube, next_position, dir) == 0)
	{
		change_pix(cube, FLOOR_MAP_C);
		cube->player->x_pos += pix_x;
		cube->player->y_pos += pix_y;
		change_pix(cube, PLAYER_C);
	}
}

static int	check_path(int dir, t_cubed *cube)
{
	if (dir == KEY_W)
	{
		move_player_forward(cube);
	}
	if (dir == KEY_A || dir == KEY_D)
	{
		move_player_side(cube, dir);
	}	
	if (dir == KEY_S)
	{
		move_player_backward(cube);
	}	
	return (0);
}

void	angle(int dir, t_cubed *cube)
{
	int	angle_max;

	angle_max = 0;
	if (dir == KEY_LEFT)
	{
		cube->player->facing_pos -= ROTATE_SPEED;
		if (cube->player->facing_pos < 0)
		{
			angle_max = cube->player->facing_pos;
			cube->player->facing_pos = 360 + angle_max;
		}
	}
	if (dir == KEY_RIGHT)
	{
		cube->player->facing_pos += ROTATE_SPEED;
		if (cube->player->facing_pos > 360)
		{
			angle_max = cube->player->facing_pos;
			cube->player->facing_pos = angle_max - 360;
		}
	}
	printf("rotation angle = %i\n", cube->player->facing_pos);
}

int	click(int keycode, t_cubed *cube)
{
	if (keycode == KEY_ESC)
	{
		free_tmp(cube);
		exit(0);
	}
	if (keycode == KEY_W)
		check_path(KEY_W, cube);
	if (keycode == KEY_S)
		check_path(KEY_S, cube);
	if (keycode == KEY_A)
		check_path(KEY_A, cube);
	if (keycode == KEY_D)
		check_path(KEY_D, cube);
	if (keycode == KEY_LEFT)
		angle(KEY_LEFT, cube);
	if (keycode == KEY_RIGHT)
		angle(KEY_RIGHT, cube);
	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_minimap, 5, 5);
	return (EXIT_SUCCESS);
}
