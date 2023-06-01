/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   collect_ext.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:29:26 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/01 22:29:26 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	change_ber(t_map *map, int x, int y)
{
	x /= 96;
	y /= 96;
	map->ber[y][x] = '0';
}

int	check_there(t_map *map, char object, int x, int y)
{
	x += map->player->instances[0].x / 96;
	y += map->player->instances[0].y / 96;
	if (map->ber[y][x] == object)
		return (1);
	return (0);
}

void	collect_ext(t_map *map)
{
	int	i;

	if (map->c_cnt == 0)
	{
		if (check_there(map, 'E', 0, 0))
		{
			map->player->instances[0].enabled = false;
			mlx_close_window(map->mlx);
		}
	}
	else if (check_there(map, 'C', 0, 0))
	{
		i = 0;
		while (map->player->instances[0].x != map->collect->instances[i].x
			|| map->player->instances[0].y != map->collect->instances[i].y)
			i++;
		map->collect->instances[i].enabled = false;
		change_ber(map, map->collect->instances[i].x,
			map->collect->instances[i].y);
		map->c_cnt--;
	}
}
