/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_hook_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:37:48 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:37:49 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	secondary_input_hook(t_game *game, char *rot)
{
	game->player->move_speed = 0.055;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		game->player->move_speed = 0.1;
	if (*rot == 'X')
	{
		game->player->rot_speed = 0.06;
		if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
			*rot = 'L';
		else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
			*rot = 'R';
	}
}

void	mouse_rotation(t_game *game, char *rot)
{
	static int32_t	mouse_pos_x = 0;
	int32_t			new_pos;
	int32_t			mouse_pos_y;

	mlx_get_mouse_pos(game->mlx, &new_pos, &mouse_pos_y);
	if (new_pos != mouse_pos_x)
	{
		game->player->rot_speed = -(mouse_pos_x - new_pos) * 0.001
			* SENSITIVITY;
		if (game->player->rot_speed > 0)
			*rot = 'R';
		else
		{
			*rot = 'L';
			game->player->rot_speed = -game->player->rot_speed;
		}
		mouse_pos_x = new_pos;
	}
}

void	input_hook(void *param)
{
	t_game	*game;
	char	dir;
	char	rot;

	dir = 'X';
	rot = 'X';
	game = param;
	mouse_rotation(game, &rot);
	secondary_input_hook(game, &rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		dir = 'W';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		dir = 'S';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		dir = 'A';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		dir = 'D';
	if ((dir != 'X' || rot != 'X'))
		player_loop(game, dir, rot);
	cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
}
