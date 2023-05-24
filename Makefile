MLXarc = MLX42/build/libmlx42.a
libft = libft/libft.a


all: $(MLXarc) libft so_long

so_long:
	gcc -o $@ $@.c $(MLXarc) $(libft) -lglfw

libft:
	make -C libft

$(MLXarc):
	cd MLX42 && cmake -B build && cmake --build build -j4

.PHONY: so_long libft