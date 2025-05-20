/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:23 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/20 14:57:31 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int esc_close(int keycode, t_cubed *cubed)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_window(cubed->mlx, cubed->win);
        free(cubed->mlx);
        exit(0);
    }
    return (0);
}
