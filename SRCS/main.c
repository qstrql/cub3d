/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:07:04 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_msg(NULL, "Wrong number of arguments, use ./cub3D <map_name.cub>");
	init_data_struct(&data);
	parse_arg(&data, argv[1]);
	parse_map(&data, argv[1]);
}
