/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:09:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/15 22:58:17 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3D.h>

static void	fill_map_colour(t_cubed *cube, int size_line, int bpp)
{
	int	map_x;
	int	map_y;
	int	pix_x;
	int pix_y;

	map_y = 0;
	pix_x = 0;
	pix_y = 0;
	while (map_y < cube->max_hei) //// mettre len de height depuis struct
	{
		map_x = 0;
		while (map_x < cube->max_wid) ///// mettre val de width depuis struct
		{
			pix_x = map_x * 10;
			pix_y = map_y * 10;
			if (cube->map_formated[map_y][map_x] == '1')
				wall_colour(pix_x, pix_y, cube, bpp, size_line);
			else if (cube->map_formated[map_y][map_x] == '0')
				walk_colour(pix_x, pix_y, cube, bpp, size_line);
			else if (cube->map_formated[map_y][map_x] == 'W' || cube->map_formated[map_y][map_x] == 'E' || cube->map_formated[map_y][map_x] == 'S' || cube->map_formated[map_y][map_x] == 'N')
				player_colour(pix_x, pix_y, cube, bpp, size_line);
			else
				break ;
			map_x++;
		}
		map_y++;
	}
}

int	minimap(t_cubed *cube)
{
    void	*ptr_minimap;
	char	*minimap;
    int		size_line;
	int		bpp;
	int		endian;

	ptr_minimap = mlx_new_image(cube->mlx, (cube->max_wid * 10), (cube->max_hei * 10)); /// changer par dimensions struct
	if (ptr_minimap == NULL)
		return (ft_printf(2, "Error: mlx failure\n"), EXIT_FAILURE);
	minimap = mlx_get_data_addr(ptr_minimap, &bpp, &size_line, &endian);
	cube->pixel_data->minimap = (unsigned char *) minimap;
	if (!cube->pixel_data->minimap)
		return (EXIT_FAILURE);
	fill_map_colour(cube, size_line, bpp); // modifier avec dimensions de struct width/height
	cube->pixel_data->bpp = bpp;
	cube->pixel_data->size_len = size_line;
	mlx_put_image_to_window(cube->mlx, cube->win, ptr_minimap, 5, 5);
	// mlx_destroy_image(cube->mlx, ptr_minimap);
	return (EXIT_SUCCESS);
}