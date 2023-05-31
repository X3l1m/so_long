#ifndef SO_LONG
# define  SO_LONG

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct
{
	mlx_t		*mlx;
	mlx_image_t	*player;
	mlx_image_t	*ext;
	mlx_image_t	*wall;
	mlx_image_t	*space;
	mlx_image_t	*collect;
	char		**ber;
	int			x;
	int			y;
	int			c_cnt;
	int			p_cnt;
	int			s_cnt;
	int			w_cnt;
	int			e_cnt;
	int			move;
}	t_map;

int map_size(t_map *map_info);
int	map_line_len(char *str, t_map *map);
int	line_count(int fd);
char**	map_init_char(int fd, int size);
void	collect_ext(t_map *map);
int	check_there(t_map *map, char object, int x, int y);

#endif