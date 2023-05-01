/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 23:10:07 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

t_mapdata  *init_mapdata(void)
{
	t_mapdata *mapdata;
	
	mapdata = malloc(sizeof(t_mapdata) * 1);
	if (!mapdata)
		return (NULL);
	mapdata->raw_file = NULL;
	mapdata->no_texture_path = NULL;
	mapdata->so_texture_path = NULL;
	mapdata->we_texture_path = NULL;
	mapdata->ea_texture_path = NULL;
	mapdata->map = NULL;
	return (mapdata);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		exit_msg("Wrong number of arguments, use ./cub3D map_name.cub");
	parse_arg(argv[1]);
	parse_map(argv[1]);
}
