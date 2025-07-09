/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:00:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/09 18:36:21 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	cpy_map(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	while (is_map(cubed, i) == false)
		i++;
	cubed->cpy_map = ft_calloc((cubed->max_hei + 1), sizeof(char *));
	if (!cubed->cpy_map)
		return (ft_printf(2, "Error: malloc cpy_map failed\n"), EXIT_FAILURE);
	y = 0;
	while (cubed->map[i])
	{
		cubed->cpy_map[y] = ft_strdup(cubed->map[i]);
		if (!cubed->cpy_map[y])
			return (ft_freetab(cubed->cpy_map), EXIT_FAILURE);
		i++;
		y++;
	}
	cubed->cpy_map[y] = NULL;
	return (EXIT_SUCCESS);
}

static int	flood_fill(t_cubed *cubed, int x, int y)
{
	if (x < 0 || y < 0 || x >= cubed->max_hei || y >= cubed->max_wid)
		return (EXIT_FAILURE);
	if (cubed->cpy_map[x][y] != '0')
		return (EXIT_SUCCESS);
	cubed->cpy_map[x][y] = 'F';
	if (flood_fill(cubed, x + 1, y) == EXIT_FAILURE || flood_fill(cubed, x - 1,
			y) == EXIT_FAILURE || flood_fill(cubed, x, y + 1) == EXIT_FAILURE
		|| flood_fill(cubed, x, y - 1) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_flood_fill(t_cubed *cubed)
{
	int	i;
	int	j;

	i = 0;
	check_max(cubed->start_map, cubed);
	if (cpy_map(cubed) == EXIT_FAILURE)
		return (ft_printf(2, "Error: copy map failed\n"), EXIT_FAILURE);
	while (cubed->cpy_map[i])
	{
		j = 0;
		while (cubed->cpy_map[i][j])
		{
			if (cubed->cpy_map[i][j] == '0')
			{
				if (flood_fill(cubed, i, j) == EXIT_FAILURE)
					return (ft_printf(2, "Error: flood fill failed\n"), ft_freetab(cubed->cpy_map),
						EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	ft_freetab(cubed->cpy_map);
	return (EXIT_SUCCESS);
}
