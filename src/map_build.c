/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_build.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:21:41 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/21 13:39:30 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	map_to_window(t_map *map, char c, int y, int x)
{
	int	i;

	x *= 96;
	y *= 96;
	i = -1;
	if (c == '1')
		i = mlx_image_to_window(map->mlx, map->wall, x, y);
	else if (c == '0' || c == 'P' || c == 'E' || c == 'C')
	{
		i = mlx_image_to_window(map->mlx, map->space, x, y);
		if (i < 0)
			return (i);
		if (c == 'C')
			i = mlx_image_to_window(map->mlx, map->collect, x, y);
		else if (c == 'P')
			i = mlx_image_to_window(map->mlx, map->player, x, y);
		else if (c == 'E')
			i = mlx_image_to_window(map->mlx, map->ext, x, y);
	}
	return (i);
}

void	texture_to_image1(t_map *map)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/wall.png");
	if (!texture)
		mlx_err(map);
	map->wall = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/space.png");
	if (!texture)
		mlx_err(map);
	map->space = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	if (!map->wall || !map->space)
		mlx_err(map);
}

void	texture_to_image(t_map *map)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/player.png");
	if (!texture)
		mlx_err(map);
	map->player = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/exit_close.png");
	if (!texture)
		mlx_err(map);
	map->ext = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/collect.png");
	if (!texture)
		mlx_err(map);
	map->collect = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	if (!map->player || !map->ext || !map->collect)
		mlx_err(map);
	texture_to_image1(map);
}

void	map_build(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	texture_to_image(map);
	while (map->y > y)
	{
		x = 0;
		while (map->x > x)
		{
			if (map_to_window(map, map->ber[y][x], y, x) < 0)
				mlx_err(map);
			x++;
		}
		y++;
	}
}

void	map_depth(t_map *map)
{
	int	i;

	i = 0;
	map->player->instances[0].z = 3;
	map->ext->instances[0].z = 1;
	while (i < map->w_cnt)
		map->wall->instances[i++].z = 1;
	i = 0;
	while (i < map->s_cnt)
		map->space->instances[i++].z = 0;
	i = 0;
	while (i < map->c_cnt)
		map->collect->instances[i++].z = 2;
}
