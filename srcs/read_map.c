/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 13:05:25 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/20 15:05:15 by enschnei         ###   ########.fr       */
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
		return (NULL);
	i = 1;
	fd = open(path, O_RDONLY);
	s = ft_calloc(10001, sizeof(char));
	stack = ft_strdup("");
	if (!s || fd == -1)
		return (free(s), free(stack), NULL);
	while (i != 0)
	{
		i = read(fd, s, 10000);
		s[i] = '\0';
		tmp = stack;
		stack = ft_strjoin(stack, s); // a proteger
		free(tmp);
	}
	close(fd);
	return (free(s), stack);
}

static int	check_newline(char *stack)
{
	int	i;

	i = 0;
	if (stack[0] == '\0')
		return (1);
	while (stack[i] != '\0')
	{
		if (stack[i] == '\n' && stack[i + 1] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	**split_map(char *path)
{
	char	**split;
	char	*stack;

	stack = read_maps(path);
	if (!stack)
		return (NULL);
	if (check_newline(stack) == 1)
	{
		ft_printf(2, "Error empty line detected\n");
		free(stack);
		return (NULL);
	}
	split = ft_split(stack, '\n');
	if (!split)
		return (ft_printf(2, "Error split\n"), NULL);
	free(stack);
	return (split);
}
