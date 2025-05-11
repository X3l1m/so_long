/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:28:05 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/03 21:21:13 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	move_direction(t_map *map, int dx, int dy)
{
	if (check_there(map, '1', dx, dy))
		return ;
	map->player->instances[0].x += dx * 96;
	map->player->instances[0].y += dy * 96;
	map->move++;
	ft_printf("%d\n", map->move);
	collect_ext(map);
}

void	move(mlx_key_data_t key, void *param)
{
	t_map	*map;

	map = param;
	if (key.action == MLX_PRESS || key.action == MLX_REPEAT)
	{
		if (key.key == MLX_KEY_W || key.key == MLX_KEY_UP)
			move_direction(map, 0, -1);
		else if (key.key == MLX_KEY_S || key.key == MLX_KEY_DOWN)
			move_direction(map, 0, 1);
		else if (key.key == MLX_KEY_D || key.key == MLX_KEY_RIGHT)
			move_direction(map, 1, 0);
		else if (key.key == MLX_KEY_A || key.key == MLX_KEY_LEFT)
			move_direction(map, -1, 0);
		else if (key.key == MLX_KEY_ESCAPE)
			mlx_close_window(map->mlx);
	}
}
