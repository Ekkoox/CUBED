/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_formated.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:42:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/09 17:40:12 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

int	is_player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	fill_end_1(t_cubed *cube, int y, int *x, int max_width)
{
	while (*x < max_width)
	{
		cube->map_formated[y][*x] = '1';
		*x += 1;
	}
	*x -= 1;
	return ;
}

int	fill_gap(int i, t_cubed *cube)
{
	int	x;
	int	y;
	
	y = 0;
	cube->map_formated = ft_calloc((cube->max_hei + 1), sizeof(char *));
	if (!cube->map_formated)
		return (EXIT_FAILURE);
	while (y < cube->max_hei)
	{
		cube->map_formated[y] = ft_calloc(cube->max_wid + 1, sizeof(char));
		if (!cube->map_formated[y])
		return (EXIT_FAILURE); ////// ajouter de quoi free le reste si erreur malloc
		y++;
	}
	y = 0;
	while (cube->map[i])
	{
		x = 0;
		while (x < cube->max_wid)
		{
			if (cube->map[i][x] == '\0')
				fill_end_1(cube, y, &x, cube->max_wid);
			else if (is_whitespace(cube->map[i][x]) == true)
				cube->map_formated[y][x] = '1';
			else if (is_valid_char(cube->map[i][x]) == true)
				cube->map_formated[y][x] = cube->map[i][x];
			x++;
		}
		cube->map_formated[y][x] = '\0';
		y++;
		i++;
	}
	return (0);
}

int	id_player_position(t_cubed *cube)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	cube->player = ft_calloc(sizeof(t_player), sizeof(t_player));
	if (!cube->player)
		return (EXIT_FAILURE);
	while (cube->map_formated[y])
	{
		x = 0;
		while (cube->map_formated[y][x])
		{
			if (is_player_pos(cube->map_formated[y][x]) == true)
			{
				cube->player->x_pos = x;
				cube->player->y_pos = y;
			}
			x++;
		}
		y++;
	}////// AJOUTER FACING POSITION ICI TEL QUE SI NORTH + 0DEG, 180DEG, 90DEG OU 360DEG
	return (EXIT_SUCCESS);
}

int	format_map(t_cubed *cube)
{
	int	i;

	i = 0;
	while (is_map(cube, i) == false)
		i++;
	check_max(i, cube);
	if (fill_gap(i, cube) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (id_player_position(cube) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
