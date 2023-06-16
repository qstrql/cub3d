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

void	check_anim(t_mapinfo *map, int frames_per_increase)
{
	int			i;
	int			j;
	static int	increase = 0;

	i = 0;
	while (i < map->height && increase == frames_per_increase)
	{
		j = 0;
		while (j < map->width && map->map[i][j])
		{
			if (map->map[i][j] >= 1 && map->map[i][j] <= 7)
				map->map[i][j] += 1;
			if (map->map[i][j] == 8)
				map->map[i][j] = 'O';
			if (map->map[i][j] >= 12 && map->map[i][j] <= 18)
				map->map[i][j] -= 1;
			if (map->map[i][j] == 11)
				map->map[i][j] = 'D';
			j++;
		}
		i++;
	}
	increase++;
	if (increase > frames_per_increase)
		increase = 0;
}

void	secondary_input_hook(t_game *game, bool *interact, char *rot)
{
	bool	map_open;

	map_open = game->player->minimap.images[0]->enabled;
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
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) && !map_open)
		*rot = 'L';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) && !map_open)
		*rot = 'R';
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
	secondary_input_hook(game, &interact, &rot);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && !map_open)
		dir = 'W';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) && !map_open)
		dir = 'S';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) && !map_open)
		dir = 'A';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) && !map_open)
		dir = 'D';
	if (dir != 'X' || rot != 'X' || interact != false)
		player_loop(game, dir, rot, interact);
	else if (!map_open)
		cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
	check_anim(game->mapinfo, 3);
}
