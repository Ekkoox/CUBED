/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:15:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/03 19:17:48 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_tmp(t_cubed *cubed)
{
	mlx_destroy_window(cubed->mlx, cubed->win);
	mlx_destroy_display(cubed->mlx);
	free(cubed->mlx);
	free_textures(cubed->imgs);
	free(cubed->pixel_data);
	ft_freetab(cubed->map);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
