/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:42:13 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/09 18:01:31 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_imgs *imgs)
{
	(void)imgs;
	if (imgs->east_texture)
		free(imgs->east_texture);
	if (imgs->west_texture)
		free(imgs->west_texture);
	if (imgs->north_texture)
		free(imgs->north_texture);
	if (imgs->south_texture)
		free(imgs->south_texture);
	if (imgs->imgs)
		free(imgs->imgs);
	free(imgs);
}
