/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:16 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/21 11:44:23 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char **av)
{
	t_cubed	cubed;

	if (ac != 2)
		return (ft_printf(2, "Error: number of arguments\n"), EXIT_FAILURE);
	cubed.map = split_map(av[1]);
	if (!cubed.map)
		return (EXIT_FAILURE); // rajouter les free
	if (error_parsing(&cubed) == EXIT_FAILURE)
		return (ft_freetab(cubed.map), EXIT_FAILURE); // rajouter les free
	if (init_mlx(&cubed) == EXIT_FAILURE)
		return (ft_freetab(cubed.map), EXIT_FAILURE); // rajouter les free
	// garbage_collector(cubed.garbage);
	ft_printf(1, "Welcolme in CUBED\n");
	mlx_hook(cubed.win, 33, 131072, free_tmp, &cubed); // changer free_tmp
	mlx_hook(cubed.win, 2, 1L, esc_close, &cubed);
    mlx_key_hook(cubed.win, 0, &cubed);
	mlx_loop(cubed.mlx);
    return (EXIT_SUCCESS);
}
