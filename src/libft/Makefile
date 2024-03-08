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

SRC = ft_atoi.c ft_split.c ft_putchar_fd.c ft_putstr_fd.c ft_strdup.c ft_strlen.c get_next_line.c get_next_line_utils.c

CC = gcc

CC_FLAGS = -Wall -Werror -Wextra

NAME = libft.a

OBJ = $(SRC:.c=.o)

all : $(NAME)

$(NAME) :
	@echo "$(YELLOW)Compiling libft... $(DEF_COLOR)"
	@$(CC) $(CC_FLAGS) -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo " "
	@echo "$(CYAN)libft compiled!$(DEF_COLOR)"

clean :
	@echo "$(YELLOW)Cleaning libft... $(DEF_COLOR)"
	@rm -f $(OBJ)
	@echo "$(CYAN)libft object files cleaned!$(DEF_COLOR)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(CYAN)libft archive cleaned!$(DEF_COLOR)"

re : fclean all

.PHONY: clean fclean
