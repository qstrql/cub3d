/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:36:28 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:41:52 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int	error_msg(char *str, int exit_code)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd("cub3D: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (exit_code);
}

void exit_msg(t_game *data, char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putstr_fd("cub3D: ", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit_program(data, EXIT_FAILURE);
}
