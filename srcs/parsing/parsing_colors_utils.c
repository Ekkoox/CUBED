/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_colors_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 19:09:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/03 19:22:00 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void init_colors(t_pixel_data *pixel_data)
{
    pixel_data->floor_color = 0;
    pixel_data->ceiling_color = 0;
}

int	validate_rgb_value(int value)
{
	return (value >= 0 && value <= 255);
}

int	parse_rgb(char *line, int *r, int *g, int *b)
{
	char	**components;
	int		i;

	line += 2;
	components = ft_split(line, ',');
	if (!components)
		return (EXIT_FAILURE);
	i = 0;
	while (components[i])
		i++;
	if (i != 3)
	{
		ft_freetab(components);
		return (EXIT_FAILURE);
	}
	*r = ft_atoi(components[0]);
	*g = ft_atoi(components[1]);
	*b = ft_atoi(components[2]);
	if (!validate_rgb_value(*r) || !validate_rgb_value(*g) || !validate_rgb_value(*b))
	{
		ft_freetab(components);
		return (EXIT_FAILURE);
	}
	ft_freetab(components);
	return (EXIT_SUCCESS);
}
