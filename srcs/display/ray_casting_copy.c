// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ray_casting_copy.c                                 :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/07/29 14:39:00 by dsatge            #+#    #+#             */
// /*   Updated: 2025/09/01 15:48:09 by dsatge           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3D.h"

// int	read_orientation(int orientation, t_cubed *cube)
// {
// 	if (orientation == NORTH)
// 		return (NORTH_C);
// 	if (orientation == SOUTH)
// 		return (SOUTH_C);
// 	if (orientation == WEST)
// 		return (WEST_C);
// 	if (orientation == EAST)
// 		return (EAST_C);
// 	if (orientation == ANGLE)
// 		return (cube->prev_color);
// 	return (cube->prev_color);
// }

// int	ray_check(double pix_x, double pix_y, t_cubed *cube)
// {
// 	unsigned long	ray;
// 	int				status;
// 	unsigned long	minimap_size;

// 	status = 0;
// 	ray = 0;
// 	minimap_size = HEIGHT * cube->pixel_data->size_len;
// 	ray = ((int)(cube->player->y_pos + (PLAYER_SIZE / 2) + (int)pix_y)
// 			* cube->pixel_data->size_len) + ((int)(cube->player->x_pos
// 				+ (PLAYER_SIZE / 2) + (int)pix_x) * (cube->pixel_data->bpp
// 				/ 8));
// 	if (ray < 0 || ray >= minimap_size || !cube->pixel_data->minimap[ray])
// 		return (1);
// 	if (cube->pixel_data->minimap[ray] == color_convert(WALL_MAP_C, BLUE))
// 		status++;
// 	if (cube->pixel_data->minimap[ray + 1] == color_convert(WALL_MAP_C, GREEN))
// 		status++;
// 	if (cube->pixel_data->minimap[ray + 2] == color_convert(WALL_MAP_C, RED))
// 		status++;
// 	if (status == 3)
// 	{
// 		cube->wall_orientation = read_orientation(cube->pixel_data->minimap[ray
// 				+ 3], cube);
// 		cube->prev_color = cube->wall_orientation;
// 		return (1);
// 	}
// 	return (0);
// }

// // void pix_projection(int x_screen, int wall_height, t_cubed *cube, double wall_hit)
// // {
// //     int tex_x;
// //     int tex_y;
// //     int screen_y;
// //     int d;
// //     char *texture;
// //     int tex_width = 64;   // largeur texture (à ajuster selon tes xpm)
// //     int tex_height = 64;  // hauteur texture

// //     // Sélectionner la bonne texture en fonction de l’orientation
// //     if (cube->wall_orientation == NORTH)
// //         texture = cube->imgs->north_texture;
// //     else if (cube->wall_orientation == SOUTH)
// //         texture = cube->imgs->south_texture;
// //     else if (cube->wall_orientation == WEST)
// //         texture = cube->imgs->west_texture;
// //     else
// //         texture = cube->imgs->east_texture;

// //     // Coordonnée X dans la texture (en fonction du point de contact du rayon)
// //     tex_x = (int)(wall_hit * (double)tex_width);
// //     if ((cube->wall_orientation == EAST || cube->wall_orientation == WEST)
// //         && cube->player->x_pos > (int)(cube->player->x_pos + wall_hit))
// //         tex_x = tex_width - tex_x - 1;

// //     // Boucler sur la hauteur du mur
// //     for (screen_y = 0; screen_y < wall_height; screen_y++)
// //     {
// //         // Calcul proportionnel entre la texture et le mur projeté
// //         tex_y = (int)((screen_y * tex_height) / wall_height);

// //         // Récupérer le pixel de la texture
// //         d = (tex_y * tex_width + tex_x) * 4; // 4 car 32 bits par pixel (bgrx)
// //         int color = *(int *)(texture + d);

// //         // Mettre le pixel dans le buffer de l’écran
// //         int i = ((HEIGHT / 2 - wall_height / 2 + screen_y) * cube->pixel_data->size_len_background)
// //                 + (x_screen * (cube->pixel_data->bpp_background / 8));
// //         *(int *)(cube->pixel_data->background + i) = color;
// //     }
// // }

// void pix_projection(int x_screen, int wall_height, t_cubed *cube, double wall_hit)
// {
//     int tex_x;
//     int tex_y;
//     int screen_y;
//     int d;
//     char *texture;
//     int tex_width = 64;
//     int tex_height = 64;
//     int start_y;

//     // Sélectionner la texture selon l'orientation réelle du mur
//     if (cube->wall_orientation == TEST_N_C)
//         texture = cube->imgs->north_texture;
//     else if (cube->wall_orientation == TEST_S_C)
//         texture = cube->imgs->south_texture;
//     else if (cube->wall_orientation == TEST_W_C)
//         texture = cube->imgs->west_texture;
//     else if (cube->wall_orientation == TEST_E_C)
//         texture = cube->imgs->east_texture;
//     else
//         return;  // Protection contre les orientations invalides

//     // Calcul de la coordonnée X de la texture
//     tex_x = (int)(wall_hit * tex_width);
//     if (tex_x < 0) tex_x = 0;
//     if (tex_x >= tex_width) tex_x = tex_width - 1;

//     // Point de départ pour centrer verticalement le mur
//     start_y = (HEIGHT - wall_height) / 2;
//     if (start_y < 0) start_y = 0;

//     // Dessiner la colonne de texture
//     for (screen_y = 0; screen_y < wall_height && (start_y + screen_y) < HEIGHT; screen_y++)
//     {
//         // Calcul de la coordonnée Y de la texture avec scaling
//         tex_y = (int)((screen_y * tex_height) / wall_height);
//         if (tex_y < 0) tex_y = 0;
//         if (tex_y >= tex_height) tex_y = tex_height - 1;

//         // Récupérer le pixel de la texture
//         d = (tex_y * tex_width + tex_x) * 4;
//         if (d >= 0 && d < (tex_width * tex_height * 4))
//         {
//             int color = *(int *)(texture + d);
            
//             // Calculer la position dans le buffer d'écran
//             int i = ((start_y + screen_y) * cube->pixel_data->size_len_background)
//                     + (x_screen * (cube->pixel_data->bpp_background / 8));
            
//             // Vérifier que la position est valide
//             if (i >= 0 && i < (HEIGHT * cube->pixel_data->size_len_background))
//             {
//                 *(int *)(cube->pixel_data->background + i) = color;
//             }
//         }
//     }
// }

// // void projection(int dist, t_cubed *cube, int x_pos)
// // {
// //     int     x;
// //     int     y;
// //     double  resolution;
// //     double  wall_height;
// //     double  scale;

// //     resolution = 1;
// //     x = x_pos;

// //     // Ajuster l'échelle pour des murs plus droits
// //     scale = (double)HEIGHT / 2.0;
    
// //     // Calcul simplifié de la hauteur du mur
// //     wall_height = (scale / (double)dist) * RESOLUTION;
    
// //     // Limiter la hauteur maximum pour éviter les déformations
// //     if (wall_height > HEIGHT)
// //         wall_height = HEIGHT;
    
// //     // Centrer le mur verticalement de manière plus précise
// //     y = (HEIGHT - wall_height) / 2.0;
// //     if (y < 0)
// //         y = 0;

// //     // Passer la hauteur du mur à pix_projection
// //     pix_projection(x, resolution, y, wall_height, cube);
// // }

// void projection(int dist, double ray_angle, t_cubed *cube, int x_pos)
// {
//     double wall_height;
//     double wall_hit;

//     // Corriger la perspective (éviter effet fish-eye)
//     double corrected_dist = dist * cos(ray_angle - (cube->player->facing_pos * M_PI / 180.0));

//     if (corrected_dist < 1) corrected_dist = 1;
//     wall_height = (HEIGHT / corrected_dist);

//     // Déterminer le point exact d'impact du rayon (entre 0 et 1)
//     if (cube->wall_orientation == EAST || cube->wall_orientation == WEST)
//         wall_hit = cube->player->y_pos + corrected_dist * sin(ray_angle);
//     else
//         wall_hit = cube->player->x_pos + corrected_dist * cos(ray_angle);

//     wall_hit -= floor(wall_hit); // garder partie fractionnelle

//     // Dessiner la colonne texturée
//     pix_projection(x_pos, wall_height, cube, wall_hit);
// }


// // void	ray_cast(t_cubed *cube, int colour, double rad, int range,
// // 		double play_angle)
// // {
// // 	double	pix_x;
// // 	double	pix_y;
// // 	int		dist;
// // 	double	corrected_dist;

// // 	dist = PLAYER_SIZE;
// // 	while ((cube->player->y_pos + dist) < WIDTH && (cube->player->x_pos
// // 			+ dist) < HEIGHT)
// // 	{
// // 		pix_x = (cos(rad) * (dist));
// // 		pix_y = (sin(rad) * (dist));
// // 		if (ray_check(pix_x, pix_y, cube) == 0)
// // 		{
// // 			pix_colour((int)pix_x, (int)pix_y, colour, cube);
// // 		}
// // 		else
// // 		{
// // 			// Calcul de la distance corrigée pour éviter l'effet fish-eye
// // 			corrected_dist = dist * cos(rad - play_angle);
// // 			projection(corrected_dist, cube, range);
// // 			break ;
// // 		}
// // 		dist += 1;
// // 	}
// // }

// void ray_cast(t_cubed *cube, double ray_angle, int x_screen)
// {
//     double pix_x = 0, pix_y = 0;  // Initialisation
//     int dist = 0;
//     int max_dist = (int)(sqrt((cube->max_wid * cube->max_wid) + 
//                    (cube->max_hei * cube->max_hei)) * RESOLUTION);

//     cube->wall_orientation = 0;  // Initialisation
//     while (dist < max_dist)
//     {
//         pix_x = cube->player->x_pos + cos(ray_angle) * dist;
//         pix_y = cube->player->y_pos + sin(ray_angle) * dist;

//         if (ray_check(pix_x, pix_y, cube))
//         {
//             projection(dist, ray_angle, cube, x_screen);
//             break;
//         }
//         dist++;
//     }
// }


// int	angle_correction(float angle)
// {
// 	if (angle < 0)
// 		angle = 360 + angle;
// 	else if (angle > 360)
// 		angle = angle - 360;
// 	return (angle);
// }

// // void	ray_vision(t_cubed *cube, int colour)
// // {
// // 	double	rad;
// // 	double	player_angle_rad;
// // 	double	ray_angle;
// // 	int		x;
// // 	double	fov_rad;

// // 	player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI
// // 			/ 180.0);
// // 	fov_rad = (VISION_WIDE * M_PI) / 180.0; // Conversion FOV en radians
// // 	ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
// // 		HEIGHT * cube->pixel_data->size_len_background);
// // 	for (x = 0; x < WIDTH; x++)
// // 	{
// // 		// Calcul uniforme de l'angle pour chaque rayon
// // 		ray_angle = player_angle_rad - (fov_rad / 2) + (x * fov_rad) / (WIDTH
// // 				- 1);
// // 		rad = ray_angle;
// // 		ray_cast(cube, colour, rad, x, player_angle_rad);
// // 	}
// // 	mlx_put_image_to_window(cube->mlx, cube->win,
// // 		cube->pixel_data->ptr_background, 0, 0);
// // }

// // void ray_vision(t_cubed *cube, int colour)
// // {
// //     double  rad;
// //     double  player_angle_rad;
// //     double  ray_angle;
// //     int     x;
// //     double  fov_rad;

// //     player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
// //     fov_rad = (VISION_WIDE * M_PI) / 180.0;
    
// //     ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
// //         HEIGHT * cube->pixel_data->size_len_background);
    
// //     for (x = 0; x < WIDTH; x++)
// //     {
// //         // Calcul de l'angle avec une correction pour éviter la distorsion
// //         double angle_ratio = (x / (double)(WIDTH - 1)) - 0.5;
// //         ray_angle = player_angle_rad + angle_ratio * fov_rad;
        
// //         rad = ray_angle;
// //         ray_cast(cube, colour, rad, x, player_angle_rad);
// //     }
    
// //     mlx_put_image_to_window(cube->mlx, cube->win,
// //         cube->pixel_data->ptr_background, 0, 0);
// // }

// void ray_vision(t_cubed *cube, int colour)
// {
// 	(void)colour;
//     double player_angle_rad = angle_correction(cube->player->facing_pos) * (M_PI / 180.0);
//     double fov_rad = (VISION_WIDE * M_PI) / 180.0;
//     int x;

//     ft_memcpy(cube->pixel_data->background, cube->pixel_data->backgr_empty,
//         HEIGHT * cube->pixel_data->size_len_background);

//     for (x = 0; x < WIDTH; x++)
//     {
//         double cameraX = 2.0 * x / (double)WIDTH - 1.0;
//         double ray_angle = player_angle_rad + atan(cameraX * tan(fov_rad / 2.0));

//         ray_cast(cube, ray_angle, x);
//     }

//     mlx_put_image_to_window(cube->mlx, cube->win,
//         cube->pixel_data->ptr_background, 0, 0);
// }
