MLXarc = MLX42/build/libmlx42.a
libft = libft/libft.a

all: $(MLXarc) $(libft)

$(libft):
	make -C libft

$(MLXarc):
	cd MLX42 && cmake -B build && cmake --build build -j4
