#include <so_long.h>

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