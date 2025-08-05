/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsatge <dsatge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:14:31 by enschnei          #+#    #+#             */
/*   Updated: 2025/08/05 14:57:17 by dsatge           ###   ########.fr       */
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
# include <math.h>

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

enum						e_colour
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
	PLAYER_C = 14176079,
	WALL_MAP_C = 9076325,
	FLOOR_MAP_C = 11183506,
	TEST_N_C = 612669,
	TEST_S_C = 1219765,
	TEST_E_C = 6033031,
	TEST_W_C = 11866916,
	SPARE_C = 15917052,
	RAY_C = 15113737,
};

enum						e_data
{
	WIDTH = 1280,
	HEIGHT = 720,
	BPP = 32,
	STEP_LEN = 2,
	ROTATE_SPEED = 10,
	PLAYER_SIZE = 2,
	RESOLUTION = 10,
	VISION_WIDE = 60,
};

enum						e_zones
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
	ANGLE = 4,
	INSIDE = 5,
};


enum						e_keys
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_LEFT = 65361,
	KEY_D = 100,
	KEY_RIGHT = 65363,
	ON_KEYDOWN = 2,
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

typedef struct s_pixel_data
{
	void					*img;
	char					*addr;
	unsigned char			*minimap;
	void					*ptr_minimap;
	void					*ptr_floor;
	void					*ptr_background;
	char					*background;
	char					*backgr_empty;
	int						play_pix_x;
	int						play_pix_y;
	int						size_len;
	int						size_len_background;
	int						bpp;
	int						bpp_background;
	int						floor_color;
	int						ceiling_color;
	int						endian;
	int						line_len;
	int						bit_pixels;
}							t_pixel_data;

typedef struct s_player
{
	double					x_pos;
	double					y_pos;
	int						facing_pos;
}							t_player;

// typedef struct s_ray
// {
// 	int						dist;
// 	int						wall_orientation;
// }							t_ray;

typedef struct s_cubed
{
	char					**map;
	char					**cpy_map;
	char					**map_formated;
	int						spwn_x;
	int						spwn_y;
	int						max_wid;
	int						max_hei;
	int						start_map;
	int						wall_orientation;
	int						prev_color;
	void					*mlx;
	void					*win;
	t_imgs					*imgs;
	t_garbage				*garbage;
	t_pixel_data			*pixel_data;
	t_player				*player;
}							t_cubed;

// Name Texture
int							stack_name_txt(t_cubed *cubed);

// Map
char						**split_map(char *path);

// Init
int							init_mlx(t_cubed *cubed);
int							init_string_textures(t_imgs *imgs);
void						check_max(int i, t_cubed *cube);

// Input
int							esc_close(int keycode, t_cubed *cubed);

// Garbadge
int							free_tmp(t_cubed *cubed);
void						free_textures(t_imgs *imgs);

// Parsing
int							error_parsing(t_cubed *cubed);
int							parsing_textures(t_cubed *cubed);
int							check_flood_fill(t_cubed *cubed); 

// Utils Parsing
int							is_map_line(const char *line);
int							validate_rgb_value(int value);
int							parsing_floor_color(t_pixel_data *pixel_data,
								char *line);
int							parsing_ceiling_color(t_pixel_data *pixel_data,
								char *line);
int							parse_rgb(char *line, int *r, int *g, int *b);
void						start_map(t_cubed *cubed);
void						init_colors(t_pixel_data *pixel_data);

// Display
int							display_floor_ceiling(t_cubed cube);
// Minimap
int							minimap(t_cubed *cube);

// Map_formated
int							format_map(t_cubed *cube);
int							is_player_pos(char c);
// Utils
int							is_whitespace(char c);
int							is_map(t_cubed *cube, int i);
int							is_white_line(char *str);

// Colours
int							color_convert(int colour, int name_colour);
void						wall_colour(int x, int y, t_cubed *cube);
void						walk_colour(int x, int y, t_cubed *cube);
void						player_colour(int x, int y, t_cubed *cube);
// Clicks
int							click(int keycode, t_cubed *cube);
void						change_pix(t_cubed *cube, int colour);
void						pix_colour(double ray_x, double ray_y, int colour, t_cubed *cube);
void						ray_vision(t_cubed *cube, int colour);
#endif