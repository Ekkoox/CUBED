/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_size_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 18:27:51 by enschnei          #+#    #+#             */
/*   Updated: 2025/08/27 18:39:40 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_size_map(t_cubed *cubed)
{
	int	line_length;
	int	i;
	int	j;

	line_length = ft_strlen(cubed->map[cubed->start_map]);
	if (line_length > 35)
		return (ft_printf(2, "Error: map is too big\n"), EXIT_FAILURE);
	i = cubed->start_map;
	while (cubed->map[i])
	{
		j = 0;
		while (cubed->map[i][j])
		{
			if (j > 35)
				return (ft_printf(2, "Error: map is too big\n"), EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
