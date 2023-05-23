NAME = domat
SRC = dom.c dene.c
FLG_LNX = -lglfw
MLX42 = ../MLX42/build/libmlx42.a -I ../MLX42/include/MLX42/

all: $(SRC)

$(SRC):
	@gcc $@ $(MLX42) $(FLG_LNX) -o $(basename $@)
	@echo Compiling $(basename $@)
.PHONY: $(SRC)