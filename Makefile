NAME = cub3d
HEADER 		=	cub3d.h
CC = gcc
CFLAGS += -Wall -Werror -Wextra -I minilibx -ggdb3
SRC = src/main.c src/render.c src/utils_1.c src/utils_memory.c
MLX_FLAGS 	= 	-L./minilibx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
INCLUDES = -I/usr/include -Imlx

OBJ = $(SRC:.c=.o)

%.o			:	%.c $(HEADER)
				$(CC) $(CFLAGS) $< -c -o $@ $(INCLUDES)

all: libmlx $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -o $(NAME)

libmlx:
	$(MAKE) -C ./minilibx/

clean:
	rm -f $(OBJ)
	make clean -C minilibx

fclean: clean
	rm -f $(NAME)

re:	fclean libmlx all

# Phony targets are used to differenciate makefile rules from system files.
.PHONY: all clean fclean re
