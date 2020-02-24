# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hturkatr <hturkatr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/01 11:38:05 by hturkatr          #+#    #+#              #
#    Updated: 2020/01/24 12:12:58 by hturkatr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_NONE = \e[0m
COLOR_WHITE = \e[1;37m
COLOR_BLUE = \e[1;34m
COLOR_GREEN = \e[1;32m
COLOR_PURPLE = \e[1;35m

NAME = lem-in
CCFL = gcc -Wall -Wextra -Werror
SRC_PATH = ./src/
SRCS = src/gnl.c src/main.c src/read_input.c src/roomlist.c src/room.c src/printing_stuff.c src/dijkstra.c src/suurballe.c src/input2_handling.c src/route.c src/ants.c src/farm.c src/freeing_stuff.c src/links_from_in_to_out_and_route_parts.c
OBJ = $(patsubst %.c,%.o,$(SRCS))
INCL = -Iincludes -Ilibft -Iminilibx_macos
FRAMEWORKS = -framework OpenGL -framework AppKit
LIBRARIES = -lftprintf -L$(LIBFT_DIR)
MINILIBX_DIR = ./minilibx_macos
MINILIBX_PATH = $(MINILIBX_DIR)/libmlx.a
LIBFT_DIR = ./printflib
LIBFT_PATH = $(LIBFT_DIR)/libprintf.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME):$(LIBFT_PATH) $(OBJ)
	@printf "$(COLOR_GREEN)Linking objects together...$(COLOR_NONE)\n"
	@$(CCFL) $(LIBRARIES) $(INCL) $(FRAMEWORKS) $(OBJ)
	@mv ./a.out $(NAME)

%.o: %.c
	@printf "$(COLOR_GREEN)Compiling $(COLOR_PURPLE)$<$(COLOR_GREEN) to $(COLOR_PURPLE)$@$(COLOR_GREEN)...$(COLOR_NONE)\n"
	@$(CCFL) $(INCL) $< -c -o $@

clean:
	@printf "$(COLOR_GREEN)Cleaning object files...$(COLOR_NONE)\n"
	@/bin/rm -f $(OBJ)
	@$(MAKE) -C $(MINILIBX_DIR) clean
	@$(MAKE) -C $(LIBFT_DIR) clean

$(MINILIBX_PATH):
	@printf "$(COLOR_GREEN)Compiling minilibx...$(COLOR_NONE)\n"
	@$(MAKE) -C $(MINILIBX_DIR)

$(LIBFT_PATH):
	@printf "$(COLOR_GREEN)Compiling libprintf...$(COLOR_NONE)\n"
	@$(MAKE) -C $(LIBFT_DIR)

fclean: clean
	@printf "$(COLOR_GREEN)Cleaning executable...$(COLOR_NONE)\n"
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(MINILIBX_PATH)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean $(NAME)