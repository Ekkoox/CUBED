/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/08/22 15:57:11 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_string_textures(t_imgs *imgs)
{
	imgs->east_texture = NULL;
	imgs->west_texture = NULL;
	imgs->north_texture = NULL;
	imgs->south_texture = NULL;
	imgs->imgs = NULL;
	return (EXIT_SUCCESS);
}

void	check_max(int i, t_cubed *cube)
{
	int	x;
	int	y;

	y = i;
	x = 0;
	cube->max_wid = 0;
	cube->max_hei = 0;
	while (cube->map[y])
	{
		x = ft_strlen(cube->map[y]);
		if (x > cube->max_wid)
			cube->max_wid = x;
		y++;
	}
	cube->max_hei = y - i;
}

// int init_texures(t_cubed *cubed)
// {
// 	int width;
// 	int height;

// 	width = 0;
// 	height = 0;
// 	cubed->imgs->north_texture = mlx_xpm_file_to_image(cubed->mlx, "textures/texture_north.xpm", &width, &height);
// 	if (!cubed->imgs->north_texture)
// 		return (ft_printf(2, "Error: Failed to load north texture\n"), EXIT_FAILURE);
// 	cubed->imgs->south_texture = mlx_xpm_file_to_image(cubed->mlx, "textures/texture_south.xpm", &width, &height);
// 	if (!cubed->imgs->south_texture)
// 		return (ft_printf(2, "Error: Failed to load south texture\n"), EXIT_FAILURE);
// 	cubed->imgs->east_texture = mlx_xpm_file_to_image(cubed->mlx, "textures/texture_east.xpm", &width, &height);
// 	if (!cubed->imgs->east_texture)
// 		return (ft_printf(2, "Error: Failed to load east texture\n"), EXIT_FAILURE);
// 	cubed->imgs->west_texture = mlx_xpm_file_to_image(cubed->mlx, "textures/texture_west.xpm", &width, &height);
// 	if (!cubed->imgs->west_texture)
// 		return (ft_printf(2, "Error: Failed to load west texture\n"), EXIT_FAILURE);
// 	cubed->imgs->ptr_north = mlx_get_data_addr(cubed->imgs->north_texture, &cubed->pixel_data->bpp, &cubed->pixel_data->line_len, &cubed->pixel_data->endian);
// 	cubed->imgs->ptr_south = mlx_get_data_addr(cubed->imgs->south_texture, &cubed->pixel_data->bpp, &cubed->pixel_data->line_len, &cubed->pixel_data->endian);
// 	cubed->imgs->ptr_east = mlx_get_data_addr(cubed->imgs->east_texture, &cubed->pixel_data->bpp, &cubed->pixel_data->line_len, &cubed->pixel_data->endian);
// 	cubed->imgs->ptr_west = mlx_get_data_addr(cubed->imgs->west_texture, &cubed->pixel_data->bpp, &cubed->pixel_data->line_len, &cubed->pixel_data->endian);
// 	return (EXIT_SUCCESS);
// }

int	init_mlx(t_cubed *cubed)
{
	cubed->mlx = mlx_init();
	if (!cubed->mlx)
		return (ft_printf(2, "Error: mlx_init failed\n"), EXIT_FAILURE);
	cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!cubed->win)
	{
		mlx_destroy_display(cubed->mlx);
		free(cubed->mlx);
		return (ft_printf(2, "Error: mlx_new_window failed\n"), EXIT_FAILURE);
	}
	// if (init_texures(cubed) == EXIT_FAILURE)
	// {
	// 	mlx_destroy_window(cubed->mlx, cubed->win);
	// 	mlx_destroy_display(cubed->mlx);
	// 	free(cubed->mlx);
	// 	return (EXIT_FAILURE);
	// }
	return (EXIT_SUCCESS);
}