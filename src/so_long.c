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
		if (i < 0)
			return (i);
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
	if (!map->wall || !map->space || !map->player || !map->ext || !map->collect || !texture)
		so_error(map, 2);
}

void	map_init(t_map *map)
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
				so_error(map, 2);
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





char	**goever(char **ber_c, int x, int y)
{
	if (ber_c[y][x] != '1')
	{
		if (ber_c[y][x] != '1')
			ber_c[y][x] = '1';
		else
			return (ber_c);
		goever(ber_c, x + 1, y);
		goever(ber_c, x - 1, y);
		goever(ber_c, x, y + 1);
		goever(ber_c, x, y - 1);
	}
	return (ber_c);
}

int	nongo(char **ber_c)
{
	int	x;
	int	y;

	y = 0;
	while (ber_c[y])
	{
		x = 0;
		while (ber_c[y][x])
		{
			if (ber_c[y][x] != '0' && ber_c[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

char **mapdup(t_map *map)
{
	char **ber_c;
	int i;

	i = 0;
	ber_c = ft_calloc(map->y + 1, sizeof(char*));
	if (!ber_c)
		exit(1);
	while (map->ber[i])
	{
		ber_c[i] = ft_strdup(map->ber[i]);
		i++;
	}
	return (ber_c);
}

void	find_player(char **ber_c, int *x, int *y)
{
	*y = 0;
	while (ber_c[*y])
	{
		*x = 0;
		while (ber_c[*y][*x])
		{
			if (ber_c[*y][*x] == 'P')
				return ;
			(*x)++;
		}
		(*y)++;
	}
}

void	free_ber(char **ber)
{
	int	i;

	i = 0;
	while (ber[i])
		free(ber[i++]);
	free(ber);
}

void	check_stuck(t_map *map)
{
	char	**ber_c;
	int		x;
	int		y;
	int		er;

	ber_c = mapdup(map);
	find_player(ber_c, &x, &y);
	er = nongo(goever(ber_c, x, y));
	free_ber(ber_c);
	if (!er)
		so_error(map, 1);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
		so_error(&map, 0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		so_error(&map, 0);
	map.ber = map_init_char(open(argv[1], O_RDONLY), line_count(fd));
	map_size(&map);
	check_stuck(&map);
	map.mlx = mlx_init(map.x * 96, map.y * 96, "SO_LONG", true);
	if (!map.mlx)
		so_error(&map, 3);
	map_init(&map);
	map_depth(&map);
	mlx_key_hook(map.mlx, &move, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}