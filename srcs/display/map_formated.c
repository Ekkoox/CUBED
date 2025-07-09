/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_formated.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:42:25 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/03 16:41:12 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

int	is_map(t_cubed *cube, int i)
{
	if (ft_strncmp(cube->map[i], "F", 1) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "C", 1) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "EA", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "WE", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "NO", 2) == 0)
		return (false);
	if (ft_strncmp(cube->map[i], "SO", 2) == 0)
		return (false);
	if (is_white_line(cube->map[i]) == true)
		return (false);
	return (true);
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

int	is_valid_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (true);
	return (false);
}

void	fill_end_1(t_cubed *cube, int y, int *x, int max_width)
{
	while (*x < max_width)
	{
		cube->map_formated[y][*x] = '1';
		*x += 1;
	}
	*x -= 1;
	return ;
}

int	fill_gap(int i, t_cubed *cube)
{
	int	x;
	int	y;
	
	y = 0;
	cube->map_formated = ft_calloc((cube->max_hei + 1), sizeof(char *));
	if (!cube->map_formated)
		return (EXIT_FAILURE);
	while (y < cube->max_hei)
	{
		cube->map_formated[y] = ft_calloc(cube->max_wid + 1, sizeof(char));
		if (!cube->map_formated[y])
		return (EXIT_FAILURE); ////// ajouter de quoi free le reste si erreur malloc
		y++;
	}
	y = 0;
	while (cube->map[i])
	{
		x = 0;
		while (x < cube->max_wid)
		{
			if (cube->map[i][x] == '\0')
				fill_end_1(cube, y, &x, cube->max_wid);
			else if (is_whitespace(cube->map[i][x]) == true)
				cube->map_formated[y][x] = '1';
			else if (is_valid_char(cube->map[i][x]) == true)
				cube->map_formated[y][x] = cube->map[i][x];
			x++;
		}
		cube->map_formated[y][x] = '\0';
		y++;
		i++;
	}
	return (0);
}

int	format_map(t_cubed *cube)
{
	int	i;

	i = 0;
	while (is_map(cube, i) == false)
		i++;
	check_max(i, cube);
	if (fill_gap(i, cube) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
