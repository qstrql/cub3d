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
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x + player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x += player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y + player->dir_y * player->move_speed)]))
			player->y += player->dir_y * player->move_speed;
	}
	else if (direction == 'S')
	{
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x - player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x -= player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y - player->dir_y * player->move_speed)]))
			player->y -= player->dir_y * player->move_speed;
	}
}

void	strafe_player(t_player *player, t_mapinfo *mapinfo, char direction)
{
	if (direction == 'A')
	{
		if (ft_strchr("0O", mapinfo->map[(int)player->x] \
		[(int)(player->y - -player->dir_x * player->move_speed)]))
			player->y -= -player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x - player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x -= player->dir_y * player->move_speed;
	}
	else if (direction == 'D')
	{
		if (ft_strchr("0O", mapinfo->map[(int)player->x] \
		[(int)(player->y + -player->dir_x * player->move_speed)]))
			player->y += -player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x + player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x += player->dir_y * player->move_speed;
	}	
}
#include <unistd.h>

void	player_interact(t_game *game)
{
	char	*tile_checked;
	char	*player_pos;
	double	time;

	tile_checked = &(game->mapinfo->map \
	[(int)(game->player->x + game->player->dir_x * 0.8)] \
	[(int)(game->player->y + game->player->dir_y * 0.8)]);
	player_pos = &(game->mapinfo->map[game->player->map_pos_x] \
			[game->player->map_pos_y]);
	if (*tile_checked == 'D')
	{
		*tile_checked = 1;
		while (*tile_checked < 10)
		{
			time = mlx_get_time();
			cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
			while (mlx_get_time() < time + 0.02)
				;
			*tile_checked += 1;
		}
		*tile_checked = 'O';
	}
	else if (*tile_checked == 'O' && *player_pos != 'O')
		*tile_checked = 'D';
}

void	player_loop(t_game *game, char direction, char rotation, bool interact)
{
	//printf("time : %f\n", mlx_get_time());
	if (rotation != 'X')
		rotate_player(game->player, rotation);
	if (direction == 'W' || direction == 'S')
		move_player(game->player, game->mapinfo, direction);
	else if (direction == 'A' || direction == 'D')
		strafe_player(game->player, game->mapinfo, direction);
	if (interact == true)
		player_interact(game);
	game->player->map_pos_x = (int)game->player->x;
	game->player->map_pos_y = (int)game->player->y;
	cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
}
