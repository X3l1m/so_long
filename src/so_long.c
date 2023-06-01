/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:29:14 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/01 22:29:14 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

int	line_count(int fd)
{
	int		i;
	char	*str;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		free(str);
		i++;
	}
	close(fd);
	return (i);
}

char	**ber_read(int fd, int size)
{
	int		i;
	char	**ber;

	i = 0;
	ber = ft_calloc(size + 1, sizeof(char *));
	if (!ber)
		exit (1);
	while (1)
	{	
		ber[i] = get_next_line(fd);
		if (!ber[i++])
			break ;
	}
	close(fd);
	return (ber);
}

void	so_error(t_map *map, int i)
{
	if (i == 0)
		ft_printf("Incorrect input!\n");
	else if (i == 1)
		ft_printf("Invalid map!\n");
	else if (i == 2)
	{
		mlx_close_window(map->mlx);
		ft_printf("%s", mlx_strerror(mlx_errno));
	}
	else if (i == 3)
		ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
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
	map.ber = ber_read(open(argv[1], O_RDONLY), line_count(fd));
	map_init(&map);
	check_stuck(&map);
	map.mlx = mlx_init(map.x * 96, map.y * 96, "SO_LONG", true);
	if (!map.mlx)
		so_error(&map, 3);
	map_build(&map);
	map_depth(&map);
	mlx_key_hook(map.mlx, &move, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	return (EXIT_SUCCESS);
}
