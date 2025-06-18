/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/17 17:54:16 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void start_map(t_cubed *cubed)
{
	int	i = 0;

	while (cubed->map[i])
	{
		if (is_map_line(cubed->map[i]))
		{
			cubed->start_map = i;
			return ;
		}
		i++;
	}
}

static int	double_char(t_cubed *cubed)
{
	int	i;
	int	y;
	int	player;

	i = cubed->start_map;
	y = 0;
	player = 0;
	while (cubed->map[i])
	{
		y = 0;
		while (cubed->map[i][y])
		{
			if ((cubed->map[i][y] == 'N' || cubed->map[i][y] == 'S'
					|| cubed->map[i][y] == 'E' || cubed->map[i][y] == 'W'))
				player++;
			y++;
		}
		i++;
	}
	if (player != 1)
		return (ft_printf(2, "Error: multiple player characters in map\n"),
			EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	error_character(t_cubed *cubed)
{
	int	i;
	int	y;

	i = cubed->start_map;
	y = 0;
	while (cubed->map[i])
	{
		y = 0;
		while (cubed->map[i][y])
		{
			if (cubed->map[i][y] != '1' && cubed->map[i][y] != '0'
				&& cubed->map[i][y] != 'N' && cubed->map[i][y] != 'S'
				&& cubed->map[i][y] != 'E' && cubed->map[i][y] != 'W'
				&& cubed->map[i][y] != ' ')
				return (ft_printf(2, "Error: invalid character in map\n"),
					EXIT_FAILURE);
			y++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	error_parsing(t_cubed *cubed)
{
	cubed->start_map = 0;
	start_map(cubed);
	if (cubed->start_map < 0)
		return (ft_printf(2, "Error: no map found\n"), EXIT_FAILURE);
	if (error_character(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (double_char(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parsing_textures(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// if (parsing_colors(cubed) == EXIT_FAILURE)
	// 	return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
