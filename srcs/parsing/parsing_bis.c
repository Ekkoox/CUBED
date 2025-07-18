/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:37:00 by enschnei          #+#    #+#             */
/*   Updated: 2025/07/17 15:42:12 by enschnei         ###   ########.fr       */
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

// static int check_open_texture(t_imgs *imgs)
// {
//     if (imgs->east_texture && open(imgs->east_texture, O_RDONLY) < 0)
//         return (ft_printf(2, "Error: cannot open east texture\n"), EXIT_FAILURE);
//     if (imgs->west_texture && open(imgs->west_texture, O_RDONLY) < 0)
//         return (ft_printf(2, "Error: cannot open west texture\n"), EXIT_FAILURE);
//     if (imgs->north_texture && open(imgs->north_texture, O_RDONLY) < 0)
//         return (ft_printf(2, "Error: cannot open north texture\n"), EXIT_FAILURE);
//     if (imgs->south_texture && open(imgs->south_texture, O_RDONLY) < 0)
//         return (ft_printf(2, "Error: cannot open south texture\n"), EXIT_FAILURE);
//     return (EXIT_SUCCESS);
// }

int parsing_textures(t_cubed *cubed)
{
    cubed->imgs = malloc(sizeof(t_imgs));
    if (!cubed->imgs)
        return (ft_printf(2, "Error: malloc imgs failed\n"), EXIT_FAILURE);
    init_string_textures(cubed->imgs);
    if (stack_name_txt(cubed) == EXIT_FAILURE)
    {
        free_textures(cubed->imgs);
        return (ft_printf(2, "Error: stack name texture failed\n"), EXIT_FAILURE);
    }
    if (cubed->imgs->east_texture == NULL || cubed->imgs->west_texture == NULL
        || cubed->imgs->north_texture == NULL || cubed->imgs->south_texture == NULL)
    {
        free_textures(cubed->imgs);
        return (ft_printf(2, "Error: missing texture\n"), EXIT_FAILURE);
    }
    if (check_double_txt(cubed->imgs) == EXIT_FAILURE)
    {
        free_textures(cubed->imgs);
        return (ft_printf(2, "Error: same texture\n"), EXIT_FAILURE);
    }
    // if (check_open_texture(cubed->imgs) == EXIT_FAILURE)
    //     return (free_textures(cubed->imgs), EXIT_FAILURE);
    return (EXIT_SUCCESS);
}
