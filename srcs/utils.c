/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:45:19 by dsatge            #+#    #+#             */
/*   Updated: 2025/07/03 16:06:56 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3D.h"

int	is_white_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f'))
			return (false);
		i++;
	}
	return (true);
}

int	is_whitespace(char c)
{
	if (!c)
		return (false);
	if (c ==  ' ' || c == '\t' || c == '\r'
			|| c == '\n' || c == '\v' || c == '\f')
			return (true);
	return (false);
}
