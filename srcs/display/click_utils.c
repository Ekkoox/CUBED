/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   click_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:01:58 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/02 17:17:20 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_cubed *cubed)
{
	if (keycode >= 0 && keycode < 70000)
		cubed->keys[keycode] = 1;
	if (keycode == KEY_ESC)
	{
		free_tmp(cubed);
		exit(0);
	}
	return (0);
}

int	key_release(int keycode, t_cubed *cubed)
{
	if (keycode >= 0 && keycode < 70000)
		cubed->keys[keycode] = 0;
	return (0);
}
