/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:54:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:05:53 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

void	init_mapdata_struct(t_mapdata *mapdata)
{
	mapdata->raw_file = NULL;
	mapdata->no_texture_path = NULL;
	mapdata->so_texture_path = NULL;
	mapdata->we_texture_path = NULL;
	mapdata->ea_texture_path = NULL;
	mapdata->floor[RED] = 0;
	mapdata->floor[GREEN] = 0;
	mapdata->floor[BLUE] = 0;
	mapdata->ceiling[RED] = 0;
	mapdata->ceiling[GREEN] = 0;
	mapdata->ceiling[BLUE] = 0;
}

void	init_data_struct(t_data *data)
{
	data->mlx = NULL;
	data->window = NULL;
	init_mapdata_struct(&data->mapdata);
	data->raw_file = NULL;
}
