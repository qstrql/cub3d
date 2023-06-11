/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:54:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/06 11:36:16 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	init_mapinfo_struct(t_mapinfo *map)
{
	map->fd = 0;
	map->line_count = 0;
	map->height = 0;
	map->width = 0;
	map->eof = 0;
	map->map_path = NULL;
	map->map = NULL;
}

void	init_config_struct(t_config *config)
{
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor.r = -1;
	config->ceiling.r = -1;
}

void	init_data_struct(t_game *data)
{
	data->mapinfo = malloc(1 * sizeof(t_mapinfo));
	data->mlx = NULL;
	init_config_struct(&data->config);
	init_mapinfo_struct(data->mapinfo);
	data->raw_file = NULL;
}
