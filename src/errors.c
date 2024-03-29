/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: seyildir <seyildir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/15 14:57:24 by seyildir      #+#    #+#                 */
/*   Updated: 2023/06/21 18:12:45 by seyildir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	so_error(int i)
{
	if (i == 0)
		ft_putstr_fd("Error\nIncorrect input!", STDERR_FILENO);
	else if (i == 1)
		ft_putstr_fd("Error\nInvalid map!", STDERR_FILENO);
	else if (i == 2)
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	write(1, "\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	mlx_err(t_map *map)
{
	str_free(map->ber);
	mlx_close_window(map->mlx);
	mlx_terminate(map->mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), STDERR_FILENO);
	write(1, "\n", STDERR_FILENO);
	exit(1);
}
