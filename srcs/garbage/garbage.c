/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:15:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/03 16:14:46 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_all(t_cubed *cubed)
{
	if (cubed->imgs && cubed->mlx)
	{
		destroy_textures(cubed);
		free(cubed->imgs);
		cubed->imgs = NULL;
	}
	if (cubed->pixel_data && cubed->mlx)
	{
		if (cubed->pixel_data->ptr_minimap)
			mlx_destroy_image(cubed->mlx, cubed->pixel_data->ptr_minimap);
		if (cubed->pixel_data->ptr_background)
			mlx_destroy_image(cubed->mlx, cubed->pixel_data->ptr_background);
		if (cubed->pixel_data->backgr_empty)
			free(cubed->pixel_data->backgr_empty);
		free(cubed->pixel_data);
		cubed->pixel_data = NULL;
	}
	if (cubed->win && cubed->mlx)
	{
		mlx_destroy_window(cubed->mlx, cubed->win);
		cubed->win = NULL;
	}
	if (cubed->mlx)
	{
		mlx_destroy_display(cubed->mlx);
		free(cubed->mlx);
		cubed->mlx = NULL;
	}
	if (cubed->map)
	{
		ft_freetab(cubed->map);
		cubed->map = NULL;
	}
	if (cubed->map_formated)
	{
		ft_freetab(cubed->map_formated);
		cubed->map_formated = NULL;
	}
	if (cubed->player)
	{
		free(cubed->player);
		cubed->player = NULL;
	}
	if (cubed->ray)
	{
		free(cubed->ray);
		cubed->ray = NULL;
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
