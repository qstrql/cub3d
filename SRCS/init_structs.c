/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:54:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/06 11:31:12 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

t_mapinfo	*init_mapinfo_struct(void)
{
	t_mapinfo *map;

	map = malloc(1 * sizeof(t_mapinfo *));
	map->fd = 0;
	map->line_count = 0;
	map->height = 0;
	map->width = 0;
	map->eof = 0;
	map->map_path = NULL;
	map->map = NULL;
	return (map);
}
void	init_config_struct(t_config *config)
{
	config->no = NULL;
	config->so = NULL;
	config->we = NULL;
	config->ea = NULL;
	config->floor = NULL;
	config->ceiling = NULL;
}

void	init_data_struct(t_game *data)
{
	data->mlx = NULL;
	init_config_struct(&data->config);
	data->mapinfo = init_mapinfo_struct();
	data->raw_file = NULL;
}
