/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/18 15:04:11 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		return (ft_printf(2, "Error: mlx_init failed\n"), EXIT_FAILURE);
	cubed->win = mlx_new_window(cubed->mlx, ft_strlen(cubed->map[0]) * 64,
			ft_count_line_split(cubed->map) * 64, "Cub3D");
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
