/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 15:27:28 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/17 14:18:00 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	error_character(t_cubed *cubed)
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
	if (error_character(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
