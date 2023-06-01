# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: seyildir <seyildir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/01 23:04:35 by seyildir      #+#    #+#                  #
#    Updated: 2023/06/01 23:07:37 by seyildir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLXarc = MLX42/build/libmlx42.a
libft = libft/libft.a

MAC_flgs = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
LNX_flgs = -lglfw
Error = -g -fsanitize=address
RM = rm -f
SRC = $(wildcard src/*.c)

all: $(MLXarc) $(libft) $(NAME)

$(NAME):
	@gcc -o $@ $(SRC) $(MLXarc) $(libft) -I ./ $(MAC_flgs)
	@echo $(NAME) creating...

$(libft):
	@make -C libft

$(MLXarc):
	@cd MLX42 && cmake -B build && cmake --build build -j4

fclean:
	@make -C libft fclean
	@make -C MLX42/build clean
	@$(RM) $(NAME)

clean:
	@make -C libft clean
	@@$(RM) $(NAME)

re: fclean all

.PHONY: fclean clean re all