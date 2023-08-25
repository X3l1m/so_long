/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:29:14 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/21 18:16:22 by seyildir      ########   odam.nl         */
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

void	check_ber_name(char *str)
{
	while (*str != '.')
	{
		str++;
		if (!*str)
			so_error(0);
	}
	if (ft_strcmp(str, ".ber"))
		so_error(0);
}

void	str_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	main(int argc, char **argv)
{
	t_map	map;
	int		fd;

	if (argc != 2)
		so_error(0);
	check_ber_name(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		so_error(0);
	map.ber = ber_read(open(argv[1], O_RDONLY), line_count(fd));
	map_init(&map);
	check_stuck(&map);
	map.mlx = mlx_init(map.x * 96, map.y * 96, "SO_LONG", false);
	if (!map.mlx)
		so_error(2);
	map_build(&map);
	map_depth(&map);
	mlx_key_hook(map.mlx, &move, &map);
	mlx_loop(map.mlx);
	mlx_terminate(map.mlx);
	str_free(map.ber);
	return (EXIT_SUCCESS);
}
