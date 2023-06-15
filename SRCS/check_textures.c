/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:29:38 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:29:39 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	verify_texture_path(t_game *data)
{
	if (file_exist(data->config.no) == false)
		return (FAIL);
	if (file_exist(data->config.so) == false)
		return (FAIL);
	if (file_exist(data->config.ea) == false)
		return (FAIL);
	if (file_exist(data->config.we) == false)
		return (FAIL);
	return (SUCCESS);
}

int	verify_minimap_textures(void)
{
	if (!file_exist("img/minimap/minimap_wall.png")
		|| !file_exist("img/minimap/map.png")
		|| !file_exist("img/minimap/minimap_player.png")
		|| !file_exist("img/minimap/minimap_ground.png")
		|| !file_exist("img/minimap/minimap_door_closed.png")
		|| !file_exist("img/minimap/minimap_door_open.png"))
		return (FAIL);
	return (SUCCESS);
}