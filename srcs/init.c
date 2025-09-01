/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:37:46 by enschnei          #+#    #+#             */
/*   Updated: 2025/08/29 18:07:59 by enschnei         ###   ########.fr       */
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

int init_textures(t_cubed *cubed)
{
    int w, h;

    if (!cubed->imgs)
    {
        cubed->imgs = malloc(sizeof(t_imgs));
        if (!cubed->imgs)
            return (ft_printf(2, "Error: malloc imgs failed\n"), EXIT_FAILURE);
    }

	cubed->imgs->ptr_east = NULL;
    cubed->imgs->ptr_west = NULL;
    cubed->imgs->ptr_north = NULL;
    cubed->imgs->ptr_south = NULL;
    cubed->imgs->east_texture = NULL;
    cubed->imgs->west_texture = NULL;
    cubed->imgs->north_texture = NULL;
    cubed->imgs->south_texture = NULL;
	
    // 1. Charger les images XPM
    cubed->imgs->ptr_east = mlx_xpm_file_to_image(cubed->mlx,
            "textures/texture_east.xpm", &w, &h);
    cubed->imgs->ptr_west = mlx_xpm_file_to_image(cubed->mlx,
            "textures/texture_west.xpm", &w, &h);
    cubed->imgs->ptr_north = mlx_xpm_file_to_image(cubed->mlx,
            "textures/texture_north.xpm", &w, &h);
    cubed->imgs->ptr_south = mlx_xpm_file_to_image(cubed->mlx,
            "textures/texture_south.xpm", &w, &h);

    if (!cubed->imgs->ptr_east || !cubed->imgs->ptr_west
        || !cubed->imgs->ptr_north || !cubed->imgs->ptr_south)
        return (ft_printf(2, "Error: failed to load textures\n"), EXIT_FAILURE);

    // 2. Obtenir les données des images
    int bpp, size_line, endian;
    cubed->imgs->east_texture = mlx_get_data_addr(cubed->imgs->ptr_east,
            &bpp, &size_line, &endian);
    cubed->imgs->west_texture = mlx_get_data_addr(cubed->imgs->ptr_west,
            &bpp, &size_line, &endian);
    cubed->imgs->north_texture = mlx_get_data_addr(cubed->imgs->ptr_north,
            &bpp, &size_line, &endian);
    cubed->imgs->south_texture = mlx_get_data_addr(cubed->imgs->ptr_south,
            &bpp, &size_line, &endian);

    return (EXIT_SUCCESS);
}


int init_mlx(t_cubed *cubed)
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
    if (init_textures(cubed) == EXIT_FAILURE)
    {
        mlx_destroy_window(cubed->mlx, cubed->win);
        mlx_destroy_display(cubed->mlx);
        free(cubed->mlx);
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}
