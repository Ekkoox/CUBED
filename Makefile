NAME = cub3D

C_FILES = main.c\
			init.c\
			input.c\
			utils.c\
			read_map.c\
			garbage/garbage.c\
			parsing/parsing.c\
			parsing/flood_fill.c\
			parsing/parsing_bis.c\
			parsing/name_texture.c\
			parsing/utils_parsing.c\
			parsing/flood_fill_utils.c\
			parsing/parsing_size_map.c\
			garbage/garbage_utils.c\
			parsing/parsing_colors_utils.c\
			display/floor_ceiling.c\
			display/minimap.c\
			display/map_formated.c\
			display/colours.c\
			display/click.c\
			display/ray_casting_copy.c\
			display/ray_casting.c\
			display/dda.c\

SRCS = $(addprefix srcs/,$(C_FILES))

# CFLAGS = -Wall -Werror -Wextra -fsanitize=address -I includes/ -g -pg
CFLAGS = -Wall -Werror -Wextra -I includes/ -g -pg

LIB = ft_printf/libftprintf.a libft/libft.a
DEPS = $(addprefix lib/,$(LIB))

all: ${NAME}

${NAME}: ${SRCS}
	make -C lib/mlx
	make -C lib/libft
	make -C lib/ft_printf
	cc ${CFLAGS} ${SRCS} -L lib/mlx -l mlx -I mlx -lXext -lX11 -lm -lz -o ${NAME} ${DEPS}

bonus:
	make -C lib/mlx
	make -C lib/libft
	make -C lib/ft_printf
	cc ${CFLAGS} ${SRCS} -L lib/mlx -l mlx -I mlx -lXext -lX11 -lm -lz -o ${NAME} ${DEPS} -D BONUS=1

clean:
	make -C lib/mlx clean
	make -C lib/libft clean
	make -C lib/ft_printf clean

fclean:	clean
		rm -rf ${NAME}

re:             fclean all

.PHONY:         all clean fclean re