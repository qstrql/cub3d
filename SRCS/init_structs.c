/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:54:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/04 16:59:46 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
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
void	init_textureinfo_struct(t_textureinfo *texture)
{
	texture->no_texture_path = NULL;
	texture->so_texture_path = NULL;
	texture->we_texture_path = NULL;
	texture->ea_texture_path = NULL;
	texture->floor[RED] = -1;
	texture->floor[GREEN] = -1;
	texture->floor[BLUE] = -1;
	texture->ceiling[RED] = -1;
	texture->ceiling[GREEN] = -1;
	texture->ceiling[BLUE] = -1;
}

void	init_data_struct(t_data *data)
{
	data->mlx = NULL;
	data->window = NULL;
	init_textureinfo_struct(&data->texture);
	init_mapinfo_struct(&data->map);
	data->raw_file = NULL;
}
