NAME = cub3d
HEADER 		=	cub3d.h
CC = gcc
CFLAGS += -Wall -Werror -Wextra -I minilibx -ggdb3
SRC = src/main.c src/render.c src/utils_1.c src/utils_memory.c src/textures.c src/raycasting.c src/file_parsing.c src/map.c src/map_check.c
MLX_FLAGS 	= 	-L./minilibx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
INCLUDES = -I/usr/include -Imlx

OBJ = $(SRC:.c=.o)

%.o			:	%.c $(HEADER)

all: libmlx $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C ./src/libft
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(MLX_FLAGS) src/libft/libft.a
	
libmlx:
	$(MAKE) -C ./minilibx/

clean:
	$(MAKE) -C ./src/libft fclean
	rm -f $(OBJ)
	make clean -C minilibx

fclean: clean
	rm -f $(NAME)

re:	fclean libmlx all

# Phony targets are used to differenciate makefile rules from system files.
.PHONY: all clean fclean re
