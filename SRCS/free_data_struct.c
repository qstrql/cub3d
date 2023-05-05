/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:52:40 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/06 00:02:14 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

void	free_mapinfo_struct(t_mapinfo *map)
{
	if (map->map_path)
		free(map->map_path);
	if (map->map)
		free_split_array(&map->map);
}
void	free_config_struct(t_config *config)
{
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
	if (config->floor)
		free(config->floor);
	if (config->ceiling)
		free(config->ceiling);
}

int	free_data_struct(t_data *data, int exit_code)
{
	free_config_struct(&data->config);
	free_mapinfo_struct(&data->map);
	if (data->raw_file)
		free_split_array(&data->raw_file);
	return (exit_code);
}
