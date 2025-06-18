/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:15:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/17 19:08:29 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int garbage_collector(t_garbage *garbage)
{
    free(garbage->cubed->map);
    printf("DU PAPIER\n");
    return (EXIT_SUCCESS);
}

int free_tmp(t_cubed *cubed)
{
    mlx_destroy_window(cubed->mlx, cubed->win);
    mlx_destroy_display(cubed->mlx);
    free(cubed->mlx);
    free_textures(cubed->imgs);
    ft_freetab(cubed->map);
    exit (EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}
