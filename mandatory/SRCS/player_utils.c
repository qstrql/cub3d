/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:39:20 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:56:54 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	rotate_player(t_player *player, char rotation)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (rotation == 'L')
	{
		player->dir_x = player->dir_x * cos(player->rot_speed)
			- player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed)
			+ player->dir_y * cos(player->rot_speed);
		player->plane_x = player->plane_x * cos(player->rot_speed)
			- player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed)
			+ player->plane_y * cos(player->rot_speed);
		return ;
	}
	player->dir_x = player->dir_x * cos(-player->rot_speed)
		- player->dir_y * sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed)
		+ player->dir_y * cos(-player->rot_speed);
	player->plane_x = player->plane_x * cos(-player->rot_speed)
		- player->plane_y * sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed)
		+ player->plane_y * cos(-player->rot_speed);
}

void	move_player(t_player *player, t_mapinfo *mapinfo, char direction)
{
	if (direction == 'W')
	{
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x + player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x += player->dir_x * player->move_speed;
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y + player->dir_y * player->move_speed)]))
			player->y += player->dir_y * player->move_speed;
	}
	else if (direction == 'S')
	{
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x - player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x -= player->dir_x * player->move_speed;
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y - player->dir_y * player->move_speed)]))
			player->y -= player->dir_y * player->move_speed;
	}
}

void	strafe_player(t_player *player, t_mapinfo *mapinfo, char direction)
{
	if (direction == 'A')
	{
		if (ft_strchr("0", mapinfo->map[(int)player->x] \
		[(int)(player->y - -player->dir_x * player->move_speed)]))
			player->y -= -player->dir_x * player->move_speed;
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x - player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x -= player->dir_y * player->move_speed;
	}
	else if (direction == 'D')
	{
		if (ft_strchr("0", mapinfo->map[(int)player->x] \
		[(int)(player->y + -player->dir_x * player->move_speed)]))
			player->y += -player->dir_x * player->move_speed;
		if (ft_strchr("0", mapinfo->map \
		[(int)(player->x + player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x += player->dir_y * player->move_speed;
	}	
}

void	player_loop(t_game *game, char direction, char rotation)
{
	if (rotation != 'X')
		rotate_player(game->player, rotation);
	if (direction == 'W' || direction == 'S')
		move_player(game->player, game->mapinfo, direction);
	else if (direction == 'A' || direction == 'D')
		strafe_player(game->player, game->mapinfo, direction);
	game->player->map_pos_x = (int)game->player->x;
	game->player->map_pos_y = (int)game->player->y;
	cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
}
