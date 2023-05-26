#include "so_long.h"

int	map_line_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*map_to_char(int fd, int *width, int *height)
{
	char	*map;
	char	*check;
	int		last_line;

	map = NULL;
	last_line = 0;
	while (check || !*height)
	{
		check = get_next_line(fd);
		*width = map_line_len(check);
		if ((*width != last_line && check && *height)
			|| (*height < 3 && !*width))
			return (0);
		if (!check)
			break ;
		if (!map)
			map = ft_strdup(check);
		else
			map = ft_strjoin_free(map, check, 3);
		last_line = *width;
		*height += 1;
	}
	*width = last_line;
	return (map);
}

int	main(void)
{
	mlx_t	*mlx;
	char	*map;
	int		width;
	int		height;

	width = 0;
	height = 0;
	map = map_to_char(open("map.ber", O_RDONLY), &width, &height);
	if (!map)
		return (1);
	char_to_window(map)
	printf("\nwidth: %d\nheight: %d\nmap:\n%s\n", width, height, map);
	mlx = mlx_init(width * 96, height * 96, "SO_LONG", false);
	mlx_loop(mlx);
	return (0);
}
