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

void	secondary_input_hook(t_game *game, bool *interact)
{
	*interact = false;
	game->player->move_speed = 0.055;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT_SHIFT))
		game->player->move_speed = 0.1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_M)
		&& !game->player->minimap.images[0]->enabled)
		display_map(game);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_N)
		&& game->player->minimap.images[0]->enabled)
		display_map(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_E))
		*interact = true;
}

void	input_hook(void *param)
{
	t_game	*game;
	char	dir;
	char	rot;
	bool	interact;
	bool	map_open;

	dir = 'X';
	rot = 'X';
	game = param;
	map_open = game->player->minimap.images[0]->enabled;
	secondary_input_hook(game, &interact);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && !map_open)
		dir = 'W';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) && !map_open)
		dir = 'S';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) && !map_open)
		dir = 'A';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) && !map_open)
		dir = 'D';
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) && !map_open)
		rot = 'L';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) && !map_open)
		rot = 'R';
	if (dir != 'X' || rot != 'X' || interact != false)
		player_loop(game, dir, rot, interact);
}
