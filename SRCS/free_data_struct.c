/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:52:40 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 23:05:23 by mjouot           ###   ########.fr       */
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
void	free_textureinfo_struct(t_textureinfo *texture)
{
	if (texture->no_texture_path)
		free(texture->no_texture_path);
	if (texture->so_texture_path)
		free(texture->so_texture_path);
	if (texture->we_texture_path)
		free(texture->we_texture_path);
	if (texture->ea_texture_path)
		free(texture->ea_texture_path);
}

int	free_data_struct(t_data *data, int exit_code)
{
	free_textureinfo_struct(&data->texture);
	if (data->raw_file)
		free_split_array(&data->raw_file);
	return (exit_code);
}
