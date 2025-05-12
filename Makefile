NAME = cub3D

C_FILES = main.c\
			read_map.c\
			garbage.c\


SRCS = $(addprefix srcs/,$(C_FILES))

CFLAGS = -Wall -Werror -Wextra -I includes/ -g

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