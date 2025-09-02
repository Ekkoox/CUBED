/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:16 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/02 16:05:21 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
	int i;
    t_cubed cubed;

	i = 0;
    if (ac != 2)
        return (ft_printf(2, "Error: number of arguments\n"), EXIT_FAILURE);
    cubed.map = split_map(av[1]);
    if (!cubed.map)
        return (EXIT_FAILURE);
    if (error_parsing(&cubed) == EXIT_FAILURE)
        return (ft_freetab(cubed.map), EXIT_FAILURE);
    if (init_mlx(&cubed) == EXIT_FAILURE)
        return (ft_freetab(cubed.map), EXIT_FAILURE);
    ft_printf(1, "Welcome in CUBED\n");
    if (format_map(&cubed) == 1)
        return (free_tmp(&cubed), EXIT_FAILURE);
    if (display_floor_ceiling(cubed) == 1)
        return (free_tmp(&cubed), EXIT_FAILURE);
    if (minimap(&cubed) == 1)
        return (free_tmp(&cubed), EXIT_FAILURE);
    ft_bzero(cubed.keys, sizeof(cubed.keys));
    while (i < 512)
        cubed.keys[i++] = 0;
    mlx_hook(cubed.win, 2, 1L << 0, key_press, &cubed);
    mlx_hook(cubed.win, 3, 1L << 1, key_release, &cubed);
    mlx_loop_hook(cubed.mlx, loop_handler, &cubed);
    mlx_hook(cubed.win, 33, 131072, free_tmp, &cubed);
    mlx_loop(cubed.mlx);
    return (EXIT_SUCCESS);
}
