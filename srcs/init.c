/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/01 11:19:40 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		return (ft_printf(2, "Error: mlx_init failed\n"), EXIT_FAILURE);
	cubed->win = mlx_new_window(cubed->mlx, 1920,
		1080, "Cub3D");
	if (!cubed->win)
	{
		mlx_destroy_display(cubed->mlx);
		free(cubed->mlx);
		return (ft_printf(2, "Error: mlx_new_window failed\n"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int init_string_textures(t_imgs *imgs)
{
    imgs->east_texture = NULL;
    imgs->west_texture = NULL;
    imgs->north_texture = NULL;
    imgs->south_texture = NULL;
    imgs->imgs = NULL;
    return (EXIT_SUCCESS);
}
