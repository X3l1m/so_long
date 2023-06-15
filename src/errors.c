/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:57:10 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/15 14:57:10 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	so_error(int i)
{
	if (i == 0)
		ft_printf("Error\nIncorrect input!\n");
	else if (i == 1)
		ft_printf("Error\nInvalid map!\n");
	else if (i == 2)
		ft_printf("%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	mlx_err(t_map *map)
{
	mlx_close_window(map->mlx);
	ft_printf("%s", mlx_strerror(mlx_errno));
}
