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

OS = $(shell uname)
CFLAGS = -I./ -Wall -Werror -Wextra
MLXarc = MLX42/build/libmlx42.a
LIBFT = libft/libft.a
SRC = $(wildcard src/*.c)
RM = rm -f

ifeq ($(OS), Darwin)
	CFLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(OS), Linux)
	CFLAGS += -lglfw -ldl -pthread -lm
endif


all: $(MLXarc) $(LIBFT) $(NAME)

$(NAME):
	@gcc -o $@ $(SRC) $(MLXarc) $(LIBFT) $(CFLAGS)
	@echo $(NAME) creating...

$(LIBFT):
	@make -C libft

$(MLXarc):
	@cd MLX42 && cmake -B build && cmake --build build -j4

fclean:
	@make -C libft fclean
	@make -C MLX42/build clean
	@$(RM) $(NAME)

clean:
	@make -C libft clean
	@$(RM) $(NAME)

re: fclean all

so_clean:
	@$(RM) $(NAME)

so_re: so_clean $(NAME)

.PHONY: fclean clean re all