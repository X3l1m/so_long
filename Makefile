MLXarc = MLX42/build/libmlx42.a
libft = libft/libft.a

MAC_flgs = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
LNX_flgs = -lglfw
Error = -g -fsanitize=address
SRC = $(wildcard src/*.c)

all: $(MLXarc) $(libft) so_long

so_long:
	@gcc -o $@ $(SRC) $(MLXarc) $(libft) -I ./ $(MAC_flgs)

$(libft):
	@make -C libft

$(MLXarc):
	@cd MLX42 && cmake -B build && cmake --build build -j4

.PHONY: so_long