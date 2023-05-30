#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42.h"

#define WIDTH 1400
#define HEIGHT 800

mlx_image_t* image;

void	move(void* param)
{
	mlx_t* mlx = param;

	if(mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if(mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 2;
	if(mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 2;
	if(mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 2;
	if(mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 2;
}

void to_to(mlx_t *mlx)
{
	mlx_image_to_window(mlx, image, 600, 5);
	mlx_image_to_window(mlx, image, 5, 5);
}

void map_to(mlx_t *mlx)
{
	to_to(mlx);
}
void mapmap(mlx_t *mlx)
{
	mlx_texture_t* texture = mlx_load_png("../textures/collectible.png");
	image = mlx_texture_to_image(mlx, texture);
}

void map_map(mlx_t *mlx)
{
	mapmap(mlx);
}

void map_depth(void)
{
	image->instances[0].z = 1;
	image->instances[1].z = 0;
	printf("%d\n%d", image->instances[0].z, image->instances[1].z);
}

int main()
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "domates", true);
	map_map(mlx);
	map_to(mlx);
	map_depth();
	//texture = mlx_load_png("patat.png");
	//image1 = mlx_texture_to_image(mlx, texture);

	mlx_loop_hook(mlx, move, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}