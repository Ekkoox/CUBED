/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:37:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/18 17:40:22 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int check_double_txt(t_imgs *imgs)
{
    if (imgs->east_texture && imgs->west_texture && imgs->north_texture
        && imgs->south_texture)
    {
        if (ft_strcmp(imgs->east_texture, imgs->west_texture) == 0
            || ft_strcmp(imgs->east_texture, imgs->north_texture) == 0
            || ft_strcmp(imgs->east_texture, imgs->south_texture) == 0
            || ft_strcmp(imgs->west_texture, imgs->north_texture) == 0
            || ft_strcmp(imgs->west_texture, imgs->south_texture) == 0
            || ft_strcmp(imgs->north_texture, imgs->south_texture) == 0)
            return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int parsing_textures(t_cubed *cubed)
{
    cubed->imgs = malloc(sizeof(t_imgs));
    if (!cubed->imgs)
        return (ft_printf(2, "Error: malloc imgs failed\n"), EXIT_FAILURE);
    init_string_textures(cubed->imgs);
    if (stack_name_txt(cubed) == EXIT_FAILURE)
    {
        free_textures(cubed->imgs);
        ft_printf(2, "Error: stack name texture failed\n");
        return (EXIT_FAILURE);
    }
    if (cubed->imgs->east_texture == NULL || cubed->imgs->west_texture == NULL
        || cubed->imgs->north_texture == NULL || cubed->imgs->south_texture == NULL)
    {
        free_textures(cubed->imgs);
        ft_printf(2, "Error: missing texture\n");
        return (EXIT_FAILURE);
    }
    if (check_double_txt(cubed->imgs) == EXIT_FAILURE)
    {
        free_textures(cubed->imgs);
        ft_printf(2, "Error: same texture\n");
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

// int parsing_colors(t_cubed *cubed)
// {
//     int i;
    
//     i = 0;
//     while (cubed->map[i])
//     {
//         if (ft_strcmp(cubed->map[i], "F ") == 0) 
            
//         i++;
//     }
//     return (EXIT_SUCCESS);
// }
