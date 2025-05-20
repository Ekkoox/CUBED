/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/20 18:48:23 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_line(t_cubed *cubed, int line)
{
	int	x;
	int	y;

	if (line)
	{
		y = 0;
		while (cubed->map[y])
			y++;
		y--;
		x = ft_strlen(cubed->map[y]);
		while (x > 0 && cubed->map[y][x - 1] == '1')
			x--;
		return (x == 0);
	}
	else
	{
		x = 0;
		while (cubed->map[0][x] == '1')
			x++;
		return (cubed->map[0][x] == '\0');
	}
}

static int	check_column(t_cubed *cubed, int column)
{
	int	y;
	int	col;

	y = 0;
	while (cubed->map[y])
	{
		if (column)
			col = ft_strlen(cubed->map[y]) - 1;
		else
			col = 0;
		if (cubed->map[y][col] != '1')
			return (EXIT_FAILURE);
		y++;
	}
	return (EXIT_SUCCESS);
}

static int	error_size(t_cubed *cubed)
{
	int		i;
	size_t	len;

	if (check_line(cubed, 0) == 0 || check_line(cubed,
			1) == 0)
		return (ft_printf(2, "Error the map is not closed\n"), EXIT_FAILURE);
	if (check_column(cubed, 0) == EXIT_FAILURE || check_column(cubed,
			1) == EXIT_FAILURE)
		return (ft_printf(2, "Error the map is not closed\n"), EXIT_FAILURE);
	i = 0;
	len = ft_strlen(cubed->map[i]);
	i++;
	while (cubed->map[i])
	{
		if (ft_strlen(cubed->map[i]) != len)
			return (ft_printf(2, "Error size map\n"), EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

static int	error_value(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (cubed->map[i])
	{
		y = 0;
		while (cubed->map[i][y])
		{
			if (cubed->map[i][y] != '1' && cubed->map[i][y] != '0'
				&& cubed->map[i][y] != 'N' && cubed->map[i][y] != 'S'
				&& cubed->map[i][y] != 'E' && cubed->map[i][y] != 'W')
				return (ft_printf(2, "Error set map\n"), EXIT_FAILURE);
			y++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	error_parsing(t_cubed *cubed)
{
	if (error_value(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (error_size(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
