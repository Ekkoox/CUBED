/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:05:25 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/03 17:04:30 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	extension_invalid(char *path)
{
	int	i;

	i = ft_strlen(path) - 4;
	return (ft_strncmp(path + i, ".cub", 4));
}

static char	*read_maps(char *path)
{
	int		i;
	int		fd;
	char	*s;
	char	*stack;
	char	*tmp;

	if (extension_invalid(path))
		return (ft_printf(2, "Error: wrong format file\n"), NULL);
	i = 1;
	fd = open(path, O_RDONLY);
	s = ft_calloc(10001, sizeof(char));
	stack = ft_strdup("");
	if (!s || fd == -1)
		return (NULL);
	while (i != 0)
	{
		i = read(fd, s, 10000);
		s[i] = '\0';
		tmp = stack;
		stack = ft_strjoin(stack, s);
		if (!stack)
			return (NULL);
		free(tmp);
	}
	close(fd);
	return (free(s), stack);
}

char	**split_map(char *path)
{
	char	**split;
	char	*stack;

	stack = read_maps(path);
	if (!stack)
		return (NULL);
	split = ft_split(stack, '\n');
	if (!split)
		return (ft_printf(2, "Error: split map\n"), NULL);
	free(stack);
	return (split);
}
