/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:38:18 by dsatge            #+#    #+#             */
/*   Updated: 2025/08/27 19:29:26 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

// static int	colour_check(t_cubed *cube, int pix_x, int pix_y)
// {
// 	double	rad;
// 	double	ray_x;
// 	double	ray_y;
// 	int		ray;

// 	rad = 0;
// 	ray_x = 0;
// 	ray_y = 0;
// 	ray = 0;
// 	while (rad < (360 * (M_PI / 180)))
// 	{
// 		ray_x = (cos(rad) * (sqrt(PLAYER_SIZE) + 1));
// 		ray_y = (sin(rad) * (sqrt(PLAYER_SIZE) + 1));
// 		ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + pix_y  + ray_y) * cube->pixel_data->size_len)
// 		+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + pix_x + ray_x) * (cube->pixel_data->bpp / 8));
// 		if (cube->pixel_data->minimap[ray + 0] == color_convert(WALL_MAP_C, BLUE))
// 			return (1);
// 		if (cube->pixel_data->minimap[ray + 1] == color_convert(WALL_MAP_C, GREEN))
// 			return (1);
// 		if (cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C, RED))
// 			return (1);
// 		rad = rad + 1 * (M_PI / 180);
// 	}
// 	return (0);
// }

// void	pix_colour(double ray_x, double ray_y, int colour, t_cubed *cube)
// {
// 	int	i;
	
// 	i = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + ray_y) * cube->pixel_data->size_len)
// 	+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + ray_x) * (cube->pixel_data->bpp / 8));
// 	cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
// 	cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
// 	cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
// }

// void	change_pix(t_cubed *cube, int colour)
// {
// 	double	rad;
// 	double	ray_x;
// 	double	ray_y;
// 	double	player_size;

// 	rad = 0;
// 	ray_x = 0;
// 	ray_y = 0;
// 	player_size = (sqrt(PLAYER_SIZE));
// 	while (player_size >= 0)
// 	{
// 		rad = 0;
// 		while (rad < (360 * (M_PI / 180)))
// 		{
// 			ray_x = (cos(rad) * player_size);
// 			ray_y = (sin(rad) * player_size);
// 			pix_colour(ray_x, ray_y, colour, cube);
// 			rad = rad + 1 * (M_PI / 180);
// 		}
// 		player_size--;
// 	}
// }

// void move_player_forward(t_cubed *cube)
// {
// 	double		rad;
// 	double		pix_x;
// 	double		pix_y;
	
// 	rad = cube->player->facing_pos * (M_PI / 180.0);
// 	pix_x = (cos(rad) * STEP_LEN);
// 	pix_y = (sin(rad) * STEP_LEN);
// 	if (colour_check(cube, pix_x, pix_y) == 0)
// 	{
// 		change_pix(cube, FLOOR_MAP_C);
// 		cube->player->x_pos += pix_x;
// 		cube->player->y_pos += pix_y;
// 		change_pix(cube, PLAYER_C);
// 	}
// }

// void move_player_backward(t_cubed *cube)
// {
// 	double		rad;
// 	double		angle;
// 	double		pix_x;
// 	double		pix_y;

// 	angle = (cube->player->facing_pos - 180);
// 	if (angle > 360)
// 		angle = angle - 360;
// 	if (angle < 0)
// 		angle = 360 + angle;
// 	rad = angle * (M_PI / 180.0);
// 	pix_x = (cos(rad) * STEP_LEN);
// 	pix_y = (sin(rad) * STEP_LEN);
// 	if (colour_check(cube, pix_x, pix_y) == 0)
// 	{
// 		change_pix(cube, FLOOR_MAP_C);
// 		cube->player->x_pos += pix_x;
// 		cube->player->y_pos += pix_y;
// 		change_pix(cube, PLAYER_C);
// 	}
// }

// void move_player_side(t_cubed *cube, int dir)
// {
// 	double		rad;
// 	double		angle;
// 	double		pix_y;
// 	double		pix_x;
	
// 	if (dir == KEY_A)
// 		angle = cube->player->facing_pos - 90;
// 	if (dir == KEY_D)
// 		angle = cube->player->facing_pos + 90;
// 	if (angle > 360)
// 		angle = angle - 360;
// 	if (angle < 0)
// 		angle = 360 + angle;
// 	rad = angle * (M_PI / 180.0);
// 	pix_x = (cos(rad) * STEP_LEN);
// 	pix_y = (sin(rad) * STEP_LEN);
// 	if (colour_check(cube, pix_x, pix_y) == 0)
// 	{
// 		change_pix(cube, FLOOR_MAP_C);
// 		cube->player->x_pos += pix_x;
// 		cube->player->y_pos += pix_y;
// 		change_pix(cube, PLAYER_C);
// 	}
// }

// static int	check_path(int dir, t_cubed *cube)
// {
// 	if (dir == KEY_W)
// 		move_player_forward(cube);
// 	if (dir == KEY_A || dir == KEY_D)
// 		move_player_side(cube, dir);	
// 	if (dir == KEY_S)
// 		move_player_backward(cube);	
// 	return (0);
// }

// void	angle(int dir, t_cubed *cube)
// {
// 	int	angle_max;

// 	angle_max = 0;
// 	if (dir == KEY_LEFT)
// 	{
// 		cube->player->facing_pos -= ROTATE_SPEED;
// 		if (cube->player->facing_pos < 0)
// 		{
// 			angle_max = cube->player->facing_pos;
// 			cube->player->facing_pos = 360 + angle_max;
// 		}
// 	}
// 	if (dir == KEY_RIGHT)
// 	{
// 		cube->player->facing_pos += ROTATE_SPEED;
// 		if (cube->player->facing_pos > 360)
// 		{
// 			angle_max = cube->player->facing_pos;
// 			cube->player->facing_pos = angle_max - 360;
// 		}
// 	}
// }

// int	click(int keycode, t_cubed *cube)
// {
// 	ray_vision(cube, FLOOR_MAP_C);
// 	if (keycode == KEY_ESC)
// 	{
// 		free_tmp(cube);
// 		exit(0);
// 	}
// 	if (keycode == KEY_W)
// 		check_path(KEY_W, cube);
// 	if (keycode == KEY_S)
// 		check_path(KEY_S, cube);
// 	if (keycode == KEY_A)
// 		check_path(KEY_A, cube);
// 	if (keycode == KEY_D)
// 		check_path(KEY_D, cube);
// 	if (keycode == KEY_LEFT)
// 		angle(KEY_LEFT, cube);
// 	if (keycode == KEY_RIGHT)
// 		angle(KEY_RIGHT, cube);
// 	ray_vision(cube, RAY_C);
// 	mlx_put_image_to_window(cube->mlx, cube->win, cube->pixel_data->ptr_minimap, 5, 5);
// 	return (EXIT_SUCCESS);
// }

static int colour_check(t_cubed *cube, double pix_x, double pix_y)
{
    double rad;
    double ray_x;
    double ray_y;
    int    ray;

    rad = 0;
    while (rad < 2 * M_PI)
    {
        ray_x = cos(rad) * (sqrt(PLAYER_SIZE) + 1);
        ray_y = sin(rad) * (sqrt(PLAYER_SIZE) + 1);

        ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + ray_y + pix_y) * cube->pixel_data->size_len)
            + ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + ray_x + pix_x) * (cube->pixel_data->bpp / 8));

        if (cube->pixel_data->minimap[ray + 0] == color_convert(WALL_MAP_C, BLUE)
         && cube->pixel_data->minimap[ray + 1] == color_convert(WALL_MAP_C, GREEN)
         && cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C, RED))
            return (1);
        rad += (M_PI / 180);
    }
    return (0);
}

void	pix_colour(double ray_x, double ray_y, int colour, t_cubed *cube)
{
	int	i;
	
	i = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + ray_y) * cube->pixel_data->size_len)
	+ ((int)(cube->player->x_pos + (PLAYER_SIZE / 2) + ray_x) * (cube->pixel_data->bpp / 8));
	cube->pixel_data->minimap[i + 0] = color_convert(colour, BLUE);
	cube->pixel_data->minimap[i + 1] = color_convert(colour, GREEN);
	cube->pixel_data->minimap[i + 2] = color_convert(colour, RED);
}

void	change_pix(t_cubed *cube, int colour)
{
	double	rad;
	double	ray_x;
	double	ray_y;
	double	player_size;

	rad = 0;
	ray_x = 0;
	ray_y = 0;
	player_size = (sqrt(PLAYER_SIZE));
	while (player_size >= 0)
	{
		rad = 0;
		while (rad < (360 * (M_PI / 180)))
		{
			ray_x = (cos(rad) * player_size);
			ray_y = (sin(rad) * player_size);
			pix_colour(ray_x, ray_y, colour, cube);
			rad = rad + 1 * (M_PI / 180);
		}
		player_size--;
	}
}

void move_player_forward(t_cubed *cube)
{
	double		rad;
	double		pix_x;
	double		pix_y;
	
	rad = cube->player->facing_pos * (M_PI / 180.0);
	pix_x = (cos(rad) * STEP_LEN);
	pix_y = (sin(rad) * STEP_LEN);
	if (colour_check(cube, pix_x, pix_y) == 0)
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
	if (colour_check(cube, pix_x, pix_y) == 0)
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
	if (colour_check(cube, pix_x, pix_y) == 0)
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
		move_player_forward(cube);
	if (dir == KEY_A || dir == KEY_D)
		move_player_side(cube, dir);	
	if (dir == KEY_S)
		move_player_backward(cube);	
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
}

int key_press(int keycode, t_cubed *cubed)
{
    if (keycode >= 0 && keycode < 70000)
        cubed->keys[keycode] = 1;
    if (keycode == KEY_ESC)
    {
        free_tmp(cubed);
        exit(0);
    }
    return (0);
}

int key_release(int keycode, t_cubed *cubed)
{
    if (keycode >= 0 && keycode < 70000)
        cubed->keys[keycode] = 0;
    return (0);
}

int loop_handler(t_cubed *cubed)
{
    if (cubed->keys[KEY_W])
        check_path(KEY_W, cubed);
    if (cubed->keys[KEY_S])
        check_path(KEY_S, cubed);
    if (cubed->keys[KEY_A])
        check_path(KEY_A, cubed);
    if (cubed->keys[KEY_D])
        check_path(KEY_D, cubed);
    if (cubed->keys[KEY_LEFT])
        angle(KEY_LEFT, cubed);
	else if (cubed->keys[KEY_RIGHT])
		angle(KEY_RIGHT, cubed);
    if (ray_vision(cubed, FLOOR_MAP_C) == EXIT_FAILURE)
		return (free_tmp(cubed), 1);
    mlx_put_image_to_window(cubed->mlx, cubed->win,
        cubed->pixel_data->ptr_minimap, 5, 5);
    return (0);
}
