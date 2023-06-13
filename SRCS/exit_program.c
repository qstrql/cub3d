/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:53:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/06 00:08:55 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	exit_game(t_game *data, int exit_code)
{
	if (!data)
		exit(exit_code);
	free_data_struct(data, exit_code);
	exit(exit_code);
}
