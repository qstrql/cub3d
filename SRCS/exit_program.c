/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:53:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 21:58:01 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

void	close_window(t_data *data)
{
	if (data->window && data->mlx)
	//	mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
	{
	//	mlx_destroy_display(data->mlx);
	//	mlx_loop_end(data->mlx);
		free(data->mlx);
	}
}

void	exit_program(t_data *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	close_window(data);
	free_data_struct(data);
	exit(exit_code);
}
