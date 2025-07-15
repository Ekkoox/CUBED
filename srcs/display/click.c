/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 15:38:18 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/15 23:02:01 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static int	next_move_check(t_cubed *cube, int dir)
{
	int	next_position;
	
	next_position = 0;
	if (dir == UP)
	{
	next_position = (cube->pixel_data->play_pix_y - (11)) * cube->pixel_data->size_len
		+ cube->pixel_data->play_pix_x * (cube->pixel_data->bpp / 8);
	}
	else if (dir == DOWN)
	{
	next_position = (cube->pixel_data->play_pix_y + (11)) * cube->pixel_data->size_len
		+ cube->pixel_data->play_pix_x * (cube->pixel_data->bpp / 8);
	}
	else if (dir == LEFT)
	{
	next_position = cube->pixel_data->play_pix_y * cube->pixel_data->size_len
		+ (cube->pixel_data->play_pix_x - (11)) * (cube->pixel_data->bpp / 8);
	}
	else if (dir == RIGHT)
	{
	next_position = cube->pixel_data->play_pix_y * cube->pixel_data->size_len
		+ (cube->pixel_data->play_pix_x + (11)) * (cube->pixel_data->bpp / 8);
	}
	return (next_position);
}

static int	colour_check(t_cubed *cube, int next_pos)
{
	int	status;
	
	status = 0;
	if (cube->pixel_data->minimap[next_pos + 0] != color_convert(11183506, BLUE))
		status++;
	if (cube->pixel_data->minimap[next_pos + 1] != color_convert(11183506, GREEN))
		status++;
	if (cube->pixel_data->minimap[next_pos + 2] != color_convert(11183506, RED))
		status++;
	if (status != 0)
		return (1);
	return (0);
}

static int	check_path(int dir, t_cubed *cube)
{
	if (dir == UP && colour_check(cube, next_move_check(cube, dir)) == 0) ///fonction qui compare couleur
	{
		printf("going up possible\n");
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = '0';
		// cube->player->y_pos--;
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = 'N';
	}
	if (dir == DOWN && colour_check(cube, next_move_check(cube, dir)) == 0) // idem
	{
		printf("going down possible\n");
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = '0';
		// cube->player->y_pos++;
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = 'N';
	}
	if (dir == LEFT && colour_check(cube, next_move_check(cube, dir)) == 0)
	{
		printf("going left possible\n");
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = '0';
		// cube->player->x_pos--;
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = 'N';
	}
	if (dir == RIGHT && colour_check(cube, next_move_check(cube, dir)) == 0)
	{	
		printf("going right possible\n");
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = '0';
		// cube->player->x_pos++;
		// cube->map_formated[cube->player->y_pos][cube->player->x_pos] = 'N';
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
		check_path(DOWN, cube);///MODIFIER
	}
	// printf("keycode = %i\n", keycode);
	if (keycode == KEY_A)
	{
		check_path(LEFT, cube);///MODIFIER    
	}
	if (keycode == KEY_D)
	{
		check_path(RIGHT, cube);///MODIFIER    
	}
	if (display_floor_ceiling(*cube) == 1)
		return (free_tmp(cube), EXIT_FAILURE);
	if (minimap(cube) == 1)
		return (free_tmp(cube), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
