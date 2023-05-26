#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "MLX42.h"

#define WIDTH 1400
#define HEIGHT 800

mlx_image_t** image;
mlx_image_t* image1;

void	move(void* param)
{
	mlx_t* mlx = param;
	int  i = 1;

	if(i == 1)
	{
		if(fabs(image[1]->instances->x - image[0]->instances->x) < 300 &&
			fabs(image[1]->instances->y - image[0]->instances->y) < 300)
		{
			mlx_delete_image(mlx, image[0]);
			i = 0;
		}
	}
	if(mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if(mlx_is_key_down(mlx, MLX_KEY_UP))
		image[1]->instances[0].y -= 2;
	if(mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image[1]->instances[0].y += 2;
	if(mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image[1]->instances[0].x += 2;
	if(mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image[1]->instances[0].x -= 2;
}


int main()
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "domates", true);
	mlx_texture_t* texture = mlx_load_png("../textures/collectible.png");
	image = malloc(sizeof(mlx_image_t));
	image[0] = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, image[0], 600, 5);
	texture = mlx_load_png("../textures/space.png");
	image[1] = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, image[1], 400, 0);
	texture = mlx_load_png("../textures/wall.png");
	image[1] = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, image[1], 200, 0);
	texture = mlx_load_png("../textures/player.png");
	image[1] = mlx_texture_to_image(mlx, texture);
	mlx_image_to_window(mlx, image[1], 0, 0);
	//texture = mlx_load_png("patat.png");
	//image1 = mlx_texture_to_image(mlx, texture);

	mlx_loop_hook(mlx, move, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}