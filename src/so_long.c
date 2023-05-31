#include <so_long.h>

int map_to_window(t_map *map, char c, int y, int x)
{
	
	int	i;

	x *= 96;
	y *= 96;
	i = -1;
	if(c == '1')
		i = mlx_image_to_window(map->mlx, map->wall, x, y);
	else if(c == '0' || c == 'P' || c == 'E' || c == 'C')
	{
		i = mlx_image_to_window(map->mlx, map->space, x, y);
		if(c == 'C')
			i = mlx_image_to_window(map->mlx, map->collect, x, y);
		else if(c == 'P')
			i = mlx_image_to_window(map->mlx, map->player, x, y);
		else if(c == 'E')
			i = mlx_image_to_window(map->mlx,map->ext, x, y);
	}
	return (i);
}

void	texture_to_image(t_map *map)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png("./textures/wall.png");
	map->wall = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/space.png");
	map->space = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/player.png");
	map->player = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/exit_close.png");
	map->ext = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
	texture = mlx_load_png("./textures/collect.png");
	map->collect = mlx_texture_to_image(map->mlx, texture);
	mlx_delete_texture(texture);
}

int	map_init(t_map *map)
{
	int y;
	int x;

	y = 0;
	texture_to_image(map);
	while (map->y > y)
	{
		x = 0;
		while (map->x > x)
		{
			if(map_to_window(map, map->ber[y][x], y, x) < 0)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
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


int	main()
{
	t_map	map;
	

	map.ber = map_init_char(open("./map.ber", O_RDONLY), line_count(open("./map.ber", O_RDONLY)));
	if(!map_size(&map))
		return (1);
	map.mlx = mlx_init(map.x * 96, map.y * 96, "SO_LONG", true);
	map_init(&map);
	map_depth(&map);
	
	mlx_key_hook(map.mlx, &move, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	system("leaks so_long");
}