/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:09:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/06/27 19:24:05 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <cub3D.h>

static int	color_convert(int colour, int name_colour)
{
	int	res;

	if (name_colour == RED)
		res = colour >> 16 & 0xFF;
	if (name_colour == GREEN)
		res = colour >> 8 & 0xFF;
	if (name_colour == BLUE)
		res = colour & 0xFF;
	return (res);
}

static void	wall_walk_colour(char *pix_char, int x, int y, int wall)
{
	int	colour;
	int	i;

	colour = 11183506;
	if (wall == true)
		colour = 9076325;
	if (wall == 2)
		colour = 14176079;
	i = y * (WIDTH * 4) + x * (BPP / 8);
	pix_char[i + 0] = color_convert(colour, BLUE);
	pix_char[i + 1] = color_convert(colour, GREEN);
	pix_char[i + 2] = color_convert(colour, RED);
	pix_char[i + 3] = 0;
}

static void	fill_map_colour(t_cubed cube, char *pix_char, int width, int height)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (y < height) //// mettre len de height depuis struct
	{
		x = 0;
		while (x < width) ///// mettre val de width depuis struct
		{
			if (cube.map[y][x] == '1')
				wall_walk_colour(pix_char, y, x, 1);
			else if (cube.map[y][x] == '0')
				wall_walk_colour(pix_char, x, y, 0);
			else if (cube.map[y][x] == 'W' || cube.map[y][x] == 'E' || cube.map[y][x] == 'S' || cube.map[y][x] == 'N')
				wall_walk_colour(pix_char, x, y, 2);
			else
				break ;
			x++;
		}
		y++;
	}
}

int	minimap(t_cubed cube)
{
    void	*ptr_minimap;
    char	*minimap;
    int		width;
	int		x;
	int		y;
	int		bpp;
	int		endian;

	x = 0;
	y = 0;
	bpp = 32;
	endian = 0;
	width = (24 * 10) * 4; ////ici entrer longueur ligne max map
	ptr_minimap = mlx_new_image(cube.mlx, width, width); /// changer par dimensions struct
	if (ptr_minimap == NULL)
		return (ft_printf(2, "Error: mlx failure\n"), EXIT_FAILURE);
	minimap = mlx_get_data_addr(ptr_minimap, &bpp, &width, &endian);
	fill_map_colour(cube, minimap, width, width); // modifier avec dimensions de struct width/height
	mlx_put_image_to_window(cube.mlx, cube.win, ptr_minimap, x, y);
	mlx_destroy_image(cube.mlx, ptr_minimap);
	return (EXIT_SUCCESS);
}