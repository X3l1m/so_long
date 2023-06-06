/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_stuck.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:29:23 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/03 20:25:37 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

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

char	**mapdup(t_map *map)
{
	char	**ber_c;
	int		i;

	i = 0;
	ber_c = ft_calloc(map->y + 1, sizeof(char *));
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

void	check_stuck(t_map *map)
{
	char	**ber_c;
	int		err;
	int		x;
	int		y;

	ber_c = mapdup(map);
	find_player(ber_c, &x, &y);
	err = nongo(goever(ber_c, x, y));
	str_free(ber_c);
	if (!err)
		so_error(1);
}
