/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 22:35:49 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/03 20:33:49 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define  SO_LONG_H

# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>

typedef struct s_map
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
	int			move;
	int			c_cnt;
	int			p_cnt;
	int			s_cnt;
	int			w_cnt;
	int			e_cnt;
}	t_map;

//map init
int		map_init(t_map *map);
//map build
void	map_build(t_map *map);
void	map_depth(t_map *map);
//check stuck
char	**goever(char **ber_c, int x, int y);
char	**mapdup(t_map *map);
void	find_player(char **ber_c, int *x, int *y);
void	check_stuck(t_map *map);
int		nongo(char **ber_c);
//error
void	so_error(int i);
void	mlx_err(t_map *map);
//move
void	move(mlx_key_data_t key, void	*param);
//collect
int		check_there(t_map *map, char object, int x, int y);
void	change_ber(t_map *map, int x, int y);
void	collect_ext(t_map *map);
//free map
void	str_free(char **str);

#endif