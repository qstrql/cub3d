/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:35:27 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:56:27 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	set_player_rotation(t_player *player, char rotation)
{
	if (rotation == 'N')
	{
		player->dir_x = -1;
		player->plane_y = 0.66;
	}
	else if (rotation == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}
	else if (rotation == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
	else if (rotation == 'E')
	{
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
}

void	set_player_init_pos(t_player *player, t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		while (j < map->width && map->map[i][j])
		{
			if (ft_strchr("NSWE", map->map[i][j]))
			{
				player->x = i + 0.5;
				player->y = j + 0.5;
				player->map_pos_x = j;
				player->map_pos_y = i;
				set_player_rotation(player, map->map[i][j]);
				map->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
		j = 0;
	}
	player->x = -1;
}

void	init_player(t_player *player, t_mapinfo *map)
{
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	set_player_init_pos(player, map);
	player->move_speed = 0.055;
	player->rot_speed = 0.08;
}
