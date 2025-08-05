/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:15:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/30 19:26:36 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_tmp(t_cubed *cubed)
{
	mlx_destroy_image(cubed->mlx, cubed->pixel_data->ptr_minimap);
	mlx_destroy_image(cubed->mlx, cubed->pixel_data->ptr_background);
	free(cubed->pixel_data->backgr_empty);
	mlx_destroy_window(cubed->mlx, cubed->win);
	mlx_destroy_display(cubed->mlx);
	free(cubed->mlx);
	free_textures(cubed->imgs);
	free(cubed->pixel_data);
	ft_freetab(cubed->map);
	ft_freetab(cubed->map_formated);
	free(cubed->player);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
