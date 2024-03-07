### COLORS ###
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

### VARIABLES ###

NAME = cub3D
NAME_BONUS = cub3D_bonus
CC = gcc
CFLAGS += -Wall -Werror -Wextra -I minilibx
MLX_FLAGS = -L./minilibx -lmlx -L/usr/lib/X11 -lXext -lX11 -lm
HEADER 	= cub3D.h
OBJF = .cache_exists	# needed to create obj/ directory
.DEFAULT_GOAL := all	# make = make all
update_flag := false

# Directories
SRC_DIR = src/
OBJ_DIR = obj/
BONUS_DIR = src/bonus/

# Source Files
SRC = main.c \
		parsing_1.c parsing_2.c parsing_3.c main.c \
		file_check.c map_check.c \
		raycaster_1.c raycaster_2.c textures.c render.c \
		movement.c key_hook.c \
		utils.c free.c free_mlx.c error.c

# Object Files
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

### COMPILATION ###

$(OBJF):
	@mkdir -p $(OBJ_DIR)

# Creating object files (.o) from source files (.c) inside the OBJ_DIR directory.
# The option -o indicates the name of the outpout, the option -c indicates the source that is used.

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADER) | $(OBJF)
	@echo "$(YELLOW)Compiling $<...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Compiling all objets files (.o) to a file "NAME" :
$(NAME) : $(OBJ)
	@$(MAKE) -C ./src/libft
	@$(CC) $(CFLAGS) $^ $(MLX_FLAGS) -o $@ ./src/libft/libft.a
	@echo " "
	@echo "$(GREEN)-> cub3D compiled!$(DEF_COLOR)"
	@echo " "
	@$(eval update_flag := true)

### BONUS ###

$(OBJ_DIR)%.o : $(BONUS_DIR)%.c $(HEADER) | $(OBJF)
	@echo "$(YELLOW)Compiling $<...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS) : $(OBJ)
	@$(CC) $(CFLAGS) $^ $(MLX_FLAGS) -o $@
	@echo " "
	@echo "$(GREEN)-> cub3D_bonus compiled!$(DEF_COLOR)"
	@echo " "

### RULES ##

nothing_to_be_done:
	@if [ "$(update_flag)" = "false" ]; then \
		echo "$(GREEN)-> make: Nothing to be done for 'all'.$(DEF_COLOR)"; \
	fi

minilibx:
	@echo "$(YELLOW)Compiling minilibx... $(DEF_COLOR)"
	@$(MAKE) -C ./minilibx/ > .mlx_outpout.txt 2>&1
	@echo " "
	@if grep -q "Nothing to be done for" .mlx_outpout.txt; then \
    	echo "$(GREEN)-> Minilibx already compiled!$(DEF_COLOR)"; \
	else \
    	echo "$(GREEN)-> Minilibx compiled!$(DEF_COLOR)"; \
	fi
	@echo " "

all: minilibx $(NAME) nothing_to_be_done
	
# Flag to check if 'clean' is executed alone or as a dependency of 'fclean'
fclean_flag := false
do_fclean:
	@$(eval fclean_flag := true)

clean:
	@echo "$(YELLOW)Cleaning cub3D... $(DEF_COLOR)"
	@echo " "
	@echo "$(YELLOW)Cleaning minilibx... $(DEF_COLOR)"
	@make clean -C minilibx
	@echo "$(CYAN)Minilibx cleaned!$(DEF_COLOR)"
	@$(MAKE) -C ./src/libft fclean
	@rm -rf $(OBJ_DIR)
	@rm -f .mlx_outpout.txt
	@echo " "
	@if [ "$(fclean_flag)" = "false" ]; then \
		echo "$(GREEN)-> cub3D object files cleaned!$(DEF_COLOR)"; \
    fi
	@if [ "$(fclean_flag)" = "true" ]; then \
		echo "$(GREEN)-> cub3D object files & executables cleaned!$(DEF_COLOR)"; \
    fi
	@echo " "

fclean: do_fclean clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)

re:	fclean minilibx all
	@echo "$(BLUE)-> Cleaned and rebuilt everything for cub3D!$(DEF_COLOR)"

# Phony targets are used to differenciate makefile rules from system files.
.PHONY: all clean fclean re minilibx bonus