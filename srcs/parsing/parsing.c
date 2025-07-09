/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/09 16:09:11 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static int	error_format(t_cubed *cubed)
{
	int	i;

	i = 0;
	while (i < cubed->start_map)
	{
		if (!(ft_strncmp(cubed->map[i], "NO ", 3) == 0
				|| ft_strncmp(cubed->map[i], "SO ", 3) == 0
				|| ft_strncmp(cubed->map[i], "WE ", 3) == 0
				|| ft_strncmp(cubed->map[i], "EA ", 3) == 0
				|| ft_strncmp(cubed->map[i], "F ", 2) == 0
				|| ft_strncmp(cubed->map[i], "C ", 2) == 0))
		{
			ft_printf(2, "Error: invalid format before map\n");
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	parsing_colors(t_cubed *cubed)
{
	int	i;

	i = 0;
	cubed->pixel_data = ft_calloc(sizeof(t_pixel_data), sizeof(t_pixel_data));
	if (!cubed->pixel_data)
		return (ft_printf(2, "Error: malloc pixel_data failed\n"),
			EXIT_FAILURE);
	init_colors(cubed->pixel_data);
	while (i < cubed->start_map)
	{
		if (ft_strncmp(cubed->map[i], "F ", 2) == 0)
		{
			if (parsing_floor_color(cubed->pixel_data,
					cubed->map[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (ft_strncmp(cubed->map[i], "C ", 2) == 0)
		{
			if (parsing_ceiling_color(cubed->pixel_data,
					cubed->map[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
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
	if (error_format(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parsing_textures(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (parsing_colors(cubed) == EXIT_FAILURE)
		return (free_textures(cubed->imgs), EXIT_FAILURE);
	// if (flood_file(cubed) == EXIT_FAILURE)
	// 	return (free_textures(cubed->imgs), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
