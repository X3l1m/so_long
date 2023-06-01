#include <so_long.h>

void	surround_wall(t_map *map)
{
	int	x;
	int y;

	y = 0;
	while (map->ber[y])
	{	
		x = 0;
		while (map->ber[y][x])
		{
			if ((y == 0 || y == (map->y - 1)) && map->ber[y][x] != '1')
				so_error(map, 1);
			if ((x == 0 || x == (map->x - 1)) && map->ber[y][x] != '1')
				so_error(map, 1);
			x++;
		}
		y++;
	}
}

int map_size(t_map *map)
{
	int	i;

	i = 0;
	map->x = 0;
	map->y = 0;
	map->move = 0;
	map->w_cnt = 0;
	map->s_cnt = 0;
	map->p_cnt = 0;
	map->e_cnt = 0;
	map->c_cnt = 0;
	while (map->ber[map->y])
	{
		i = map_line_len(map->ber[map->y], map);
		if ((i != map->x && map->y))
			so_error(map, 1);
		map->x = i;
		map->y++;
	}
	if (map->x < 3 || map->y < 3)
		so_error(map, 1);
	if (map->p_cnt < 1 || map->e_cnt < 1 || map->w_cnt < 1
		|| map->s_cnt < 1 || map->c_cnt < 1 || map->w_cnt < 1)
		so_error(map, 1);
	surround_wall(map);
	return (1);
}

void	object_count(char c, t_map *map)
{
	if(c == '1')
		map->w_cnt++;
	else if (c == '0' || c == 'P' || c == 'E' || c == 'C')
	{
		map->s_cnt++;
		if(c == 'C')
			map->c_cnt++;
		else if(c == 'P')
			map->p_cnt++;
		else if(c == 'E')
			map->e_cnt++;
	}
	else
		so_error(map, 1);
	if (map->p_cnt > 1 || map->e_cnt > 1)
		so_error(map, 1);
}

int	map_line_len(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		object_count(str[i], map);
		i++;
	}
	if(str[i] == '\n')
		str[i] = 0;
	return (i);
}

int	line_count(int fd)
{
	int		i;
	char	*str;
	i = 0;
	while(1)
	{
		str = get_next_line(fd);
		if(!str)
			break;
		free(str);
		i++;
	}
	close(fd);
	return (i);
}

char**	map_init_char(int fd, int size)
{
	int		i;
	char	**ber;

	i = 0;
	ber = malloc(sizeof(char*) * (size + 1));
	if (!ber)
		exit (1);
	while (1)
	{	
		ber[i] = get_next_line(fd);
		if (!ber[i++])
			break;
	}
	close(fd);
	return (ber);
}

void	change_map(t_map *map, int x, int y)
{
	x /= 96;
	y /= 96;
	map->ber[y][x] = '0';
}

void	collect_ext(t_map *map)
{
	int	i;

	i = 0;
	if(map->c_cnt == 0)
	{
		if (check_there(map, 'E', 0, 0))
		{
			map->player->instances[0].enabled = false;
			mlx_close_window(map->mlx);
		}
	}
	if(check_there(map, 'C', 0, 0))
	{
		while (map->player->instances[0].x != map->collect->instances[i].x 
			|| map->player->instances[0].y != map->collect->instances[i].y)
			i++;
		map->collect->instances[i].enabled = false;
		change_map(map, map->collect->instances[i].x, map->collect->instances[i].y);
		map->c_cnt--;
	}
	return ;
}