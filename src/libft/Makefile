# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/14 09:42:21 by kschouft          #+#    #+#              #
#    Updated: 2024/03/07 23:43:56 by acosi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

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
	@rm -f $(BONUS_OBJ)
	@echo "$(BLUE)libft object files cleaned!$(DEF_COLOR)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(BLUE)libft archive cleaned!$(DEF_COLOR)"

re : fclean all

.PHONY: clean fclean
