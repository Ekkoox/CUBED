/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:43:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/05 13:22:27 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int stack_name_txt_west(t_cubed *cubed)
{
	int i;
	int y;

	i = 0;
	while(cubed->map[i])
	{
		y = 0;
		while(is_whitespace(cubed->map[i][y]) == true)
			y++;
		if (ft_strncmp(cubed->map[i] + y, "WE", 2) == 0)
		{
			cubed->imgs->west_texture = ft_strdup(cubed->map[i] + y + 3);
			if (!cubed->imgs->west_texture)
			{
				free(cubed->imgs->north_texture);
				free(cubed->imgs->south_texture);
				return (ft_printf(2, "Error: memory allocation failed\n"),
					EXIT_FAILURE);
			}
		}
		i++;
	}
	return(EXIT_SUCCESS);
}

int	stack_name_txt_south(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	while (cubed->map[i])
	{
		y = 0;
		while(is_whitespace(cubed->map[i][y]) == true)
			y++;
		if (ft_strncmp(cubed->map[i] + y, "SO", 2) == 0)
		{
			cubed->imgs->south_texture = ft_strdup(cubed->map[i] + y + 3);
			if (!cubed->imgs->south_texture)
			{
				free(cubed->imgs->north_texture);
				return (ft_printf(2, "Error: memory allocation failed\n"),
					EXIT_FAILURE);
			}
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	stack_name_txt_east(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	while (cubed->map[i])
	{
		y = 0;
		while(is_whitespace(cubed->map[i][y]) == true)
			y++;
		if (ft_strncmp(cubed->map[i] + y, "EA", 2) == 0)
		{
			cubed->imgs->east_texture = ft_strdup(cubed->map[i] + y + 3);
			if (!cubed->imgs->east_texture)
				return (free(cubed->imgs->west_texture),
					free(cubed->imgs->south_texture),
					free(cubed->imgs->north_texture), ft_printf(2,
						"Error: memory allocation failed\n"), EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	stack_name_txt_north(t_cubed *cubed)
{
	int	i;
	int	y;

	i = 0;
	while (cubed->map[i])
	{
		y = 0;
		while(is_whitespace(cubed->map[i][y]) == true)
			y++;
		if (ft_strncmp(cubed->map[i] + y, "NO", 2) == 0)
		{
			cubed->imgs->north_texture = ft_strdup(cubed->map[i] + y + 3);
			if (!cubed->imgs->north_texture)
				return (ft_printf(2, "Error: memory allocation failed\n"),
					EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	stack_name_txt(t_cubed *cubed)
{
	if (stack_name_txt_north(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (stack_name_txt_south(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (stack_name_txt_west(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (stack_name_txt_east(cubed) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
