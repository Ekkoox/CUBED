/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 14:57:23 by enschnei          #+#    #+#             */
/*   Updated: 2025/09/02 16:16:35 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	esc_close(int keycode, t_cubed *cubed)
{
	if (keycode == KEY_ESC)
	{
		free_tmp(cubed);
		exit(0);
	}
	return (0);
}
