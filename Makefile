# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkellum <nkellum@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/13 12:50:22 by nkellum           #+#    #+#              #
#    Updated: 2019/01/17 10:46:54 by nkellum          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRC = main.c
OBJ = $(SRC:.c=.o)

# This is a minimal set of ANSI/VT100 color codes
_END=\x1b[0m
_BOLD=\x1b[1m
_UNDER=\x1b[4m
_REV=\x1b[7m

# Colors
_GREY=\x1b[30m
_RED=\x1b[31m
_GREEN=\x1b[32m
_YELLOW=\x1b[33m
_BLUE=\x1b[34m
_PURPLE=\x1b[35m
_CYAN=\x1b[36m
_WHITE=\x1b[37m


all: $(NAME)

$(NAME):
	@#-@ make -C libft
	@#@echo "${_YELLOW}Compiled Libft${_END}"
	@cc -o $(NAME) -I /usr/local/include $(SRC) -L ./minilibx -lmlx \
	-framework OpenGL -framework AppKit libft/libft.a
	@echo "${_GREEN}Compiled fdf${_END}"

%.o: %.c libft.h
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)
	@#@make -C libft clean

fclean: clean
	@rm -f $(NAME)
	@#@make -C libft fclean

re: fclean all