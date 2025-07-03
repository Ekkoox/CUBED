/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:16 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/03 16:47:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void            my_mlx_pixel_put(t_pixel_data *data, int x, int y, int color)
{
  char    *dst;

  dst = data->addr + (y * data->line_len + x * (data->bit_pixels / 8));
  *(unsigned int*)dst = color;
}

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
	ft_printf(1, "Welcome in CUBED\n");
	if (format_map(&cubed) == 1)
		return (free_tmp(&cubed), EXIT_FAILURE);
	mlx_hook(cubed.win, 33, 131072, free_tmp, &cubed); // changer free_tmp
	mlx_hook(cubed.win, 2, 1L, esc_close, &cubed);
    // mlx_key_hook(cubed.win, 0, &cubed);
	if (display_floor_ceiling(cubed) == 1)
		return (free_tmp(&cubed), EXIT_FAILURE);
	if (minimap(&cubed) == 1)
		return (free_tmp(&cubed), EXIT_FAILURE);
	mlx_loop(cubed.mlx);
	return (EXIT_SUCCESS);
}
