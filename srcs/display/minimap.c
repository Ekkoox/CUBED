/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:09:44 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/03 17:13:45 by dsatge           ###   ########.fr       */
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

static void	wall_walk_colour(char *pix_char, int x, int y, int wall, t_cubed *cube)
{
	int	colour;
	int	i;

	colour = 11183506;
	if (wall == true)
		colour = 9076325;
	if (wall == 2)
		colour = 14176079;
	i = y * ((cube->max_wid) * 4) + x * (BPP / 8);
	pix_char[i + 0] = color_convert(colour, BLUE);
	pix_char[i + 1] = color_convert(colour, GREEN);
	pix_char[i + 2] = color_convert(colour, RED);
	pix_char[i + 3] = 0;
}

static void	fill_map_colour(t_cubed *cube, char *pix_char, int width, int height)
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
			if (cube->map_formated[y][x] == '1')
				wall_walk_colour(pix_char, y, x, 1, cube);
			else if (cube->map_formated[y][x] == '0')
				wall_walk_colour(pix_char, x, y, 0, cube);
			else if (cube->map_formated[y][x] == 'W' || cube->map_formated[y][x] == 'E' || cube->map_formated[y][x] == 'S' || cube->map_formated[y][x] == 'N')
				wall_walk_colour(pix_char, x, y, 2, cube);
			else
				break ;
			x++;
		}
		y++;
	}
}

int	minimap(t_cubed *cube)
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
	width = (cube->max_wid) * 4;
	// width = (24 + 1); ////ici entrer longueur ligne max map
	ptr_minimap = mlx_new_image(cube->mlx, cube->max_wid, cube->max_hei); /// changer par dimensions struct
	if (ptr_minimap == NULL)
		return (ft_printf(2, "Error: mlx failure\n"), EXIT_FAILURE);
	minimap = mlx_get_data_addr(ptr_minimap, &bpp, &width, &endian);
	fill_map_colour(cube, minimap, cube->max_wid, cube->max_hei); // modifier avec dimensions de struct width/height
	mlx_put_image_to_window(cube->mlx, cube->win, ptr_minimap, x, y);
	mlx_destroy_image(cube->mlx, ptr_minimap);
	return (EXIT_SUCCESS);
}