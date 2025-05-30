/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:15:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/20 15:55:17 by enschnei         ###   ########.fr       */
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
    ft_freetab(cubed->map);
    exit (EXIT_SUCCESS);
    return (EXIT_SUCCESS);
}
