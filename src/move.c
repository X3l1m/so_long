#include <so_long.h>

void	move_up(t_map *map)
{
	if(check_there(map, '1', 0, -1))
		return ;
	map->player->instances[0].y -= 96;
	map->move++;
	ft_printf("%d\n", map->move);
	collect_ext(map);
}

void	move_donw(t_map *map)
{
	if(check_there(map, '1', 0, 1))
		return ;
	map->player->instances[0].y += 96;
	map->move++;
	ft_printf("%d\n", map->move);
	collect_ext(map);
}

void	move_right(t_map *map)
{
	if(check_there(map, '1', 1, 0))
		return ;
	map->player->instances[0].x += 96;
	map->move++;
	ft_printf("%d\n", map->move);
	collect_ext(map);
}

void	move_left(t_map *map)
{
	if(check_there(map, '1', -1, 0))
		return ;
	map->player->instances[0].x -= 96;
	map->move++;
	ft_printf("%d\n", map->move);
	collect_ext(map);
}

int	check_there(t_map *map, char object, int x, int y)
{
	x += map->player->instances[0].x / 96;
	y += map->player->instances[0].y / 96;
	if (map->ber[y][x] == object)
		return (1);
	return(0);
}

void	move(mlx_key_data_t key, void* param)
{
	t_map *map;

	map = param;
	if (key.action == MLX_PRESS)
	{
		if(key.key == MLX_KEY_UP)
			move_up(map);
		else if(key.key == MLX_KEY_DOWN)
			move_donw(map);
		else if(key.key == MLX_KEY_RIGHT)
			move_right(map);
		else if(key.key == MLX_KEY_LEFT)
			move_left(map);
		else if(key.key == MLX_KEY_ESCAPE)
			mlx_close_window(map->mlx);
	}
}