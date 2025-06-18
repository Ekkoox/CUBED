/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:14:31 by enschnei          #+#    #+#             */
/*   Updated: 2025/06/18 15:04:34 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include "../lib/mlx/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

enum						e_keys
{
	KEY_ESC = 65307,
	KEY_W = 119,
	// KEY_UP = 65362,
	KEY_S = 115,
	// KEY_DOWN = 65364,
	KEY_A = 97,
	KEY_LEFT = 65361,
	KEY_D = 100,
	KEY_RIGHT = 65363,
};

typedef struct s_cubed		t_cubed;
typedef struct s_imgs		t_imgs;
typedef struct s_garbage	t_garbage;

typedef struct s_imgs
{
	void					*imgs;
	char					*east_texture;
	char					*west_texture;
	char					*north_texture;
	char					*south_texture;
}							t_imgs;

typedef struct s_garbage
{
	int						tqt;
	t_cubed					*cubed;
}							t_garbage;

typedef struct s_cubed
{
	int						start_map;
	char					**map;
	void					*mlx;
	void					*win;
	t_imgs					*imgs;
	t_garbage				*garbage;
}							t_cubed;

// Name Texture
int							stack_name_txt(t_cubed *cubed);

// Map
char						**split_map(char *path);

// Init
int							init_mlx(t_cubed *cubed);
int 						init_string_textures(t_imgs *imgs);

// Input
int							esc_close(int keycode, t_cubed *cubed);

// Garbadge
int							free_tmp(t_cubed *cubed);
int							garbage_collector(t_garbage *garbage);
void						free_textures(t_imgs *imgs);

// Parsing
int							error_parsing(t_cubed *cubed);
int 						parsing_textures(t_cubed *cubed);

// Utils Parsing
int							is_map_line(const char *line);

#endif