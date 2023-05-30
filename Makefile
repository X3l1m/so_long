MLXarc = MLX42/build/libmlx42.a
libft = libft/libft.a

SRC = $(wildcard src/*.c)

all: $(MLXarc) libft so_long

so_long:
	@gcc -o $@ $(SRC) $(MLXarc) $(libft) -lglfw -I ./

$(libft):
	@make -C libft

$(MLXarc):
	@cd MLX42 && cmake -B build && cmake --build build -j4

.PHONY: so_long libft