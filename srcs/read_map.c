/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:05:25 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/04 16:43:54 by enschnei         ###   ########.fr       */
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

	i = 1;
	fd = open(path, O_RDONLY);
	s = ft_calloc(10001, sizeof(char));
	stack = ft_strdup("");
	if (!s || fd == -1)
		return (ft_printf(2, "Error: open map\n"), free(s), free(stack), NULL);
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

static int	is_line_empty(char *content, int start, int end)
{
	int	j;

	j = start;
	while (j < end)
	{
		if (content[j] != ' ' && content[j] != '\t')
			return (0);
		j++;
	}
	return (1);
}

static int	check_empty_lines_map(char *content)
{
	int	i;
	int	j;
	int	map_started;
	int	line_start;

	i = 0;
	map_started = 0;
	while (content[i])
	{
		line_start = i;
		while (content[i] && content[i] != '\n')
			i++;
		if (!map_started)
		{
			j = line_start;
			while (j < i && (content[j] == ' ' || content[j] == '\t'))
				j++;
			if (j < i && (content[j] == '1' || content[j] == '0'
					|| content[j] == ' '))
				map_started = 1;
		}
		else if (map_started && is_line_empty(content, line_start, i))
			return (EXIT_FAILURE);
		if (content[i++] == '\n')
			i++;
	}
	return (EXIT_SUCCESS);
}

char	**split_map(char *path)
{
	char	**split;
	char	*stack;

	if (extension_invalid(path))
		return (ft_printf(2, "Error: wrong format file\n"), NULL);
	stack = read_maps(path);
	if (!stack)
		return (NULL);
	if (check_empty_lines_map(stack) == EXIT_FAILURE)
	{
		ft_printf(2, "Error: the map contains empty lines\n");
		free(stack);
		return (NULL);
	}
	split = ft_split(stack, '\n');
	if (!split)
		return (ft_printf(2, "Error: split map\n"), free(stack), NULL);
	free(stack);
	return (split);
}
