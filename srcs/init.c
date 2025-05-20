/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/20 15:35:01 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int init_mlx(t_cubed *cubed)
{
    cubed->mlx = mlx_init();
    if (!cubed->mlx)
        return (ft_printf(2, "Error: mlx_init failed\n"), EXIT_FAILURE);
    printf("mlx = %p\n", cubed->mlx);
    cubed->win = mlx_new_window(cubed->mlx, 800, 600, "Cub3D");
    if (!cubed->win)
    {
        mlx_destroy_display(cubed->mlx);
        free(cubed->mlx);
        return (ft_printf(2, "Error: mlx_new_window failed\n"), EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
