/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
/*   Updated: 2025/09/01 19:45:24 by dsatge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	orientation_color(t_cubed *cube)
{
	if (cube->ray->dda == VERTICAL && cube->ray->step_x == 1)
		return (EAST_C);
	else if (cube->ray->dda == VERTICAL && cube->ray->step_x == -1)
		return (WEST_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == 1)
		return (SOUTH_C);
	else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == -1)
		return (NORTH_C);
	return (0);
}

int	angle_correction(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 360)
		angle = angle - 360;
	return (angle);
}

// void	draw_projection(t_cubed *cube, double perp_dist, int x_start, int x_end)
// {
// 	int	i;
// 	int	x;
// 	int	color;
// 	int	draw_start;
// 	int	draw_end;

// 	draw_start = -((int)(HEIGHT / perp_dist)) / 1 + HEIGHT / 2;
// 	draw_end = ((int)(HEIGHT / perp_dist)) / 1 + HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	if (draw_end >= HEIGHT)
// 		draw_end = HEIGHT - 1;
// 	while (draw_start++ <= draw_end)
// 	{
// 		x = x_start;
// 		while (x++ <= x_end)
// 		{
// 			i = (draw_start * cube->pixel_data->size_len_background)
// 				+ (x * (cube->pixel_data->bpp_background / 8));
// 			color = orientation_color(cube);
// 			cube->pixel_data->background[i + 0] = color_convert(color, BLUE);
// 			cube->pixel_data->background[i + 1] = color_convert(color, GREEN);
// 			cube->pixel_data->background[i + 2] = color_convert(color, RED);
// 		}
// 	}
// }

// int	get_texture_pixel(char *texture, int tex_x, int tex_y, int tex_width)
// {
//     int	pixel_index;
    
//     pixel_index = (tex_y * tex_width + tex_x) * 4; // 4 bytes par pixel (BGRA)
//     return (*(int *)(texture + pixel_index));
// }

int	get_texture_pixel(char *texture, int tex_x, int tex_y, int tex_width)
{
    int	pixel_index;
    
    // Vérifications de sécurité intégrées
    if (tex_x < 0 || tex_x >= tex_width || tex_y < 0 || tex_y >= 64)
        return (0);
    
    pixel_index = (tex_y * tex_width + tex_x) * 4;
    return (*(int *)(texture + pixel_index));
}

// char	*get_wall_texture(t_cubed *cube)
// {
//     if (cube->ray->dda == VERTICAL && cube->ray->step_x == 1)
//         return (cube->imgs->east_texture);
//     else if (cube->ray->dda == VERTICAL && cube->ray->step_x == -1)
//         return (cube->imgs->west_texture);
//     else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == 1)
//         return (cube->imgs->south_texture);
//     else if (cube->ray->dda == HORIZONTAL && cube->ray->step_y == -1)
//         return (cube->imgs->north_texture);
//     return (NULL);
// }

char	*get_wall_texture(t_cubed *cube)
{
    // Utiliser un switch peut être plus rapide que des if-else
    if (cube->ray->dda == VERTICAL)
    {
        return (cube->ray->step_x == 1) ? cube->imgs->east_texture : cube->imgs->west_texture;
    }
    else
    {
        return (cube->ray->step_y == 1) ? cube->imgs->south_texture : cube->imgs->north_texture;
    }
}

// void	draw_textured_wall(t_cubed *cube, int draw_start, int draw_end, 
//     int x_start, int x_end, double wall_hit, int wall_height)
// {
//     char	*texture;
//     int		tex_width = 64;
//     int		tex_height = 64;
//     int		tex_x;
//     int		tex_y;
//     int		x, y;
//     int		i;
//     int		color;
    
//     // Sélectionner la texture selon l'orientation
//     texture = get_wall_texture(cube);
//     if (!texture)
//         return;
    
//     // Calculer la coordonnée X de la texture
//     tex_x = (int)(wall_hit * tex_width);
//     if (tex_x < 0) tex_x = 0;
//     if (tex_x >= tex_width) tex_x = tex_width - 1;
    
//     // Dessiner la colonne texturée
//     for (y = draw_start; y <= draw_end; y++)
//     {
//         // Calculer la coordonnée Y de la texture
//         tex_y = (int)(((y - draw_start) * tex_height) / wall_height);
//         if (tex_y < 0) tex_y = 0;
//         if (tex_y >= tex_height) tex_y = tex_height - 1;
        
//         // Récupérer la couleur du pixel de la texture
//         color = get_texture_pixel(texture, tex_x, tex_y, tex_width);
        
//         // Dessiner sur tous les pixels de la largeur
//         for (x = x_start; x <= x_end; x++)
//         {
//             i = (y * cube->pixel_data->size_len_background)
//                 + (x * (cube->pixel_data->bpp_background / 8));
//             *(int *)(cube->pixel_data->background + i) = color;
//         }
//     }
// }

void	draw_textured_wall(t_cubed *cube, int draw_start, int draw_end, 
    int x_start, int x_end, double wall_hit, int wall_height)
{
    char	*texture;
    int		tex_x;
    int		tex_y;
    int		x, y;
    int		i;
    int		color;
    double	tex_step;
    double	tex_pos;
    int		line_offset;
    
    texture = get_wall_texture(cube);
    if (!texture)
        return;
    
    // Précalculer tex_x une seule fois
    tex_x = (int)(wall_hit * 64);
    if (tex_x < 0) tex_x = 0;
    if (tex_x >= 64) tex_x = 63;
    
    // Précalculer le step pour la texture Y
    tex_step = 64.0 / wall_height;
    tex_pos = (draw_start - (-wall_height + HEIGHT) / 2) * tex_step;
    
    // Précalculer certaines valeurs constantes
    int bytes_per_pixel = cube->pixel_data->bpp_background / 8;
    int size_line = cube->pixel_data->size_len_background;
    
    // Boucle optimisée
    for (y = draw_start; y <= draw_end; y++)
    {
        tex_y = (int)tex_pos;
        if (tex_y >= 64) tex_y = 63;
        
        // Récupérer la couleur une seule fois par ligne
        color = get_texture_pixel(texture, tex_x, tex_y, 64);
        
        // Précalculer l'offset de ligne
        line_offset = y * size_line;
        
        // Dessiner sur tous les pixels de la largeur
        for (x = x_start; x <= x_end; x++)
        {
            i = line_offset + (x * bytes_per_pixel);
            *(int *)(cube->pixel_data->background + i) = color;
        }
        tex_pos += tex_step;
    }
}

// void	draw_projection(t_cubed *cube, double perp_dist, int x_start, int x_end)
// {
//     // int		i;
//     // int		x;
//     int		draw_start;
//     int		draw_end;
//     int		wall_height;
//     double	wall_hit;
    
//     wall_height = (int)(HEIGHT / perp_dist);
//     draw_start = -(wall_height) / 2 + HEIGHT / 2;
//     draw_end = wall_height / 2 + HEIGHT / 2;
//     if (draw_start < 0)
//         draw_start = 0;
//     if (draw_end >= HEIGHT)
//         draw_end = HEIGHT - 1;
    
//     // Calculer le point d'impact pour les textures
//     if (cube->ray->dda == VERTICAL)
//         wall_hit = cube->ray->player_pos_y + perp_dist * cube->ray->ray_rad_y;
//     else
//         wall_hit = cube->ray->player_pos_x + perp_dist * cube->ray->ray_rad_x;
//     wall_hit -= floor(wall_hit);
    
//     draw_textured_wall(cube, draw_start, draw_end, x_start, x_end, wall_hit, wall_height);
// }

void	draw_projection(t_cubed *cube, double perp_dist, int x_start, int x_end)
{
    int		draw_start;
    int		draw_end;
    int		wall_height;
    double	wall_hit;
    
    wall_height = (int)(HEIGHT / perp_dist);
    draw_start = (-wall_height + HEIGHT) / 2;  // Simplifié
    draw_end = (wall_height + HEIGHT) / 2;     // Simplifié
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= HEIGHT)
        draw_end = HEIGHT - 1;
    
    // Calculer le point d'impact pour les textures
    if (cube->ray->dda == VERTICAL)
        wall_hit = cube->ray->player_pos_y + perp_dist * cube->ray->ray_rad_y;
    else
        wall_hit = cube->ray->player_pos_x + perp_dist * cube->ray->ray_rad_x;
    wall_hit -= floor(wall_hit);
    
    draw_textured_wall(cube, draw_start, draw_end, x_start, x_end, wall_hit, wall_height);
}

void	pix_projection_column(int screen_x, int ray_width, double perp_dist,
	t_cubed *cube)
{
	int	x_start;
	int	x_end;

	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	x_start = screen_x * ray_width;
	x_end = x_start + ray_width - 1;
	if (x_start < 0)
		x_start = 0;
	if (x_end >= WIDTH)
		x_end = WIDTH - 1;
	draw_projection(cube, perp_dist, x_start, x_end);
}

void	ray_cast(t_cubed *cube, int screen_x)
{
	double	perp_dist;

	dda(cube);
	if (cube->ray->dda == VERTICAL)
		perp_dist = (cube->ray->move_spot_x - cube->ray->player_pos_x
				+ (1.0 - cube->ray->step_x) * 0.5) / cube->ray->ray_rad_x;
	else
		perp_dist = (cube->ray->move_spot_y - cube->ray->player_pos_y
				+ (1.0 - cube->ray->step_y) * 0.5) / cube->ray->ray_rad_y;
	if (cube->ray->dda == VERTICAL)
		perp_dist = cube->ray->dist_line_x - cube->ray->delta_x;
	if (cube->ray->dda == HORIZONTAL)
		perp_dist = cube->ray->dist_line_y - cube->ray->delta_y;
	perp_dist = perp_dist * cos(cube->ray->rad - (angle_correction(cube->player->facing_pos)
				* (M_PI / 180.0)));
	if (perp_dist < 1e-6)
		perp_dist = 1e-6;
	pix_projection_column(screen_x, RAY_PER_PIX, perp_dist, cube);
}

int	ray_vision(t_cubed *cube)
{
    double	fov_rad;
    int		total_rays;
    int		ray;
    double	angle_step;
    double	base_angle;
    
    fov_rad = (VISION_WIDE * M_PI) / 180.0;
    total_rays = WIDTH;
    
    // Précalculer les valeurs constantes
    angle_step = fov_rad / (double)(total_rays - 1);
    base_angle = (angle_correction(cube->player->facing_pos) * (M_PI / 180.0)) - (fov_rad / 2.0);
    
    ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
        HEIGHT * cube->pixel_data->size_len_background);
    cube->ray = ft_calloc(1, sizeof(t_ray));
    if (!cube->ray)
        return (EXIT_FAILURE);
    
    ray = -1;
    while (++ray < total_rays)
    {
        // Calcul optimisé de l'angle
        cube->ray->rad = base_angle + (ray * angle_step);
        if (ray % RAY_PER_PIX == 0)
			ray_cast(cube, ray  / RAY_PER_PIX);
    }
    mlx_put_image_to_window(cube->mlx, cube->win,
        cube->pixel_data->ptr_background, 0, 0);
    return (0);
}

// int	ray_vision(t_cubed *cube)
// {
// 	double	fov_rad;
// 	int		total_rays;
// 	int		ray;

// 	fov_rad = (VISION_WIDE * M_PI) / 180.0;
// 	total_rays = WIDTH * RAY_PER_PIX;
// 	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
// 		HEIGHT * cube->pixel_data->size_len_background);
// 	cube->ray = ft_calloc(1, sizeof(t_ray));
// 	if (!cube->ray)
// 		return (EXIT_FAILURE);
// 	ray = -1;
// 	while (++ray < total_rays)
// 	{
// 		cube->ray->rad = (angle_correction(cube->player->facing_pos)
// 				* (M_PI / 180.0))
// 			- (fov_rad / 2.0) + (ray * fov_rad) / (double)(total_rays - 1);
// 		if (ray % RAY_PER_PIX == 0)
// 			ray_cast(cube, ray / RAY_PER_PIX);
// 	}
// 	mlx_put_image_to_window(cube->mlx, cube->win,
// 		cube->pixel_data->ptr_background, 0, 0);
// 	return (0);
// }
