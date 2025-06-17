/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/17 16:09:02 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int is_map_line(const char *line)
{
	if (!line)
		return (0);
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
		return (0);
	if (*line == '\0' || *line == '\n')
		return (0);
	while (*line)
	{
		if (*line == '1' || *line == '0' || *line == 'N'
			|| *line == 'S' || *line == 'E' || *line == 'W'
			|| *line == ' ')
			return (1);
		line++;
	}
	return (0);
}

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
	printf("start_map: %d\n", cubed->start_map);
	if (cubed->start_map < 0)
		return (ft_printf(2, "Error: no map found\n"), EXIT_FAILURE);
	if (error_character(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (double_char(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
