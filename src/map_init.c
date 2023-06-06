/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:26:57 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/03 20:26:46 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	object_count(char c, t_map *map)
{
	if (c == '1')
		map->w_cnt++;
	else if (c == '0' || c == 'P' || c == 'E' || c == 'C')
	{
		map->s_cnt++;
		if (c == 'C')
			map->c_cnt++;
		else if (c == 'P')
			map->p_cnt++;
		else if (c == 'E')
			map->e_cnt++;
	}
	else
		so_error(1);
	if (map->p_cnt > 1 || map->e_cnt > 1)
		so_error(1);
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
	if (str[i] == '\n')
		str[i] = 0;
	return (i);
}

void	surround_wall(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->ber[y])
	{	
		x = 0;
		while (map->ber[y][x])
		{
			if ((y == 0 || y == (map->y - 1)) && map->ber[y][x] != '1')
				so_error(1);
			if ((x == 0 || x == (map->x - 1)) && map->ber[y][x] != '1')
				so_error(1);
			x++;
		}
		y++;
	}
}

int	map_init(t_map *map)
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
			so_error(1);
		map->x = i;
		map->y++;
	}
	if (map->x < 3 || map->y < 3)
		so_error(1);
	if (map->p_cnt < 1 || map->e_cnt < 1 || map->c_cnt < 1 || map->w_cnt < 7)
		so_error(1);
	surround_wall(map);
	return (1);
}
