#include <so_long.h>

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
			return (0);
		map->x = i;
		map->y++;
	}
	if (map->x < 3 || map->y < 3)
		return (0);
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
		exit(1);
	if (map->p_cnt > 1 || map->e_cnt > 1)
		exit(1);
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
	//ft_printf("%d", size);
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

int	check_there(t_map *map, char object, int x, int y)
{
	x += map->player->instances[0].x / 96;
	y += map->player->instances[0].y / 96;
	if (map->ber[y][x] == object)
		return (1);
	return(0);
}

void	collect_ext(t_map *map)
{
	int	i;

	i = 0;
	if(map->c_cnt <= 0)
	{
		if (check_there(map, 'E', 0, 0))
			map->player->instances[0].enabled = false;
	}
	if(check_there(map, 'C', 0, 0))
	{
		while (map->player->instances[0].x != map->collect->instances[i].x 
			|| map->player->instances[0].y != map->collect->instances[i].y)
			i++;
		map->collect->instances[i].enabled = false;
		
		map->c_cnt--;
	}
}

void	change_map()