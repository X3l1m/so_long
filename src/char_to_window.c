#include "so_long.h"

int map_size(t_map *map)
{
	int	i;

	i = 0;
	map->x = 0;
	map->y = 0;
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
	int	i;

	i = 0;
	while (get_next_line(fd))
		i++;
	return (i);
}

char**	map_init_char(int fd, int size)
{
	int		i;
	char	**ber;

	i = 0;
	ber = malloc(sizeof(char*) * size);
	if (!ber)
		return (0);
	while (1)
	{	
		ber[i] = get_next_line(fd);
		if (!ber[i++])
			return(ber);
	}
	return (ber);
}
