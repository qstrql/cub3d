/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:52:40 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:06:07 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

void	free_mapdata_struct(t_mapdata *mapdata)
{
	if (mapdata->raw_file)
		free(mapdata->raw_file);
	if (mapdata->no_texture_path)
		free(mapdata->no_texture_path);
	if (mapdata->so_texture_path)
		free(mapdata->so_texture_path);
	if (mapdata->we_texture_path)
		free(mapdata->we_texture_path);
	if (mapdata->ea_texture_path)
		free(mapdata->ea_texture_path);
}

void	free_data_struct(t_data *data)
{
	free_mapdata_struct(&data->mapdata);
	if (data->raw_file)
		free_split_array(&data->raw_file);
}
