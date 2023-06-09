# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: seyildir <seyildir@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/06/01 23:04:35 by seyildir      #+#    #+#                  #
#    Updated: 2023/06/03 19:51:44 by seyildir      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = so_long

MLX42 = MLX42/build/libmlx42.a
LIBFT = libft/libft.a

CFLAGS = -Wall -Werror -Wextra
LIBS = $(LIBFT) $(MLX42) $(LIBFT)

OS = $(shell uname)

ifeq ($(OS), Darwin)
	EXT = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(OS), Linux)
	EXT = -lglfw -ldl -pthread -lm
endif

SRC_DIR = ./src
OBJ_DIR = ./obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

RM = rm -f

all: $(MLX42) $(LIBFT) $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	gcc $(CFLAGS) -o $@ -c $< -I ./
	
$(NAME): $(OBJ)
	@gcc -o $@ $(OBJ) -I ./ $(LIBS) $(EXT)
	@echo $(NAME) creating...

$(LIBFT):
	@make -C libft

$(MLX42):
	@cd MLX42 && cmake -B build && cmake --build build -j4

fclean:
	@make -C libft fclean
	@$(RM)r MLX42/build
	@$(RM) $(NAME)
	@$(RM)r $(OBJ_DIR)

clean:
	@make -C libft clean
	@$(RM)r $(OBJ_DIR)


re: fclean all

.PHONY: fclean clean re all