/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:56:34 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	check_textures_not_corrupted(t_config config)
{
	if (!config.textures[0] || !config.textures[1] || !config.textures[2]
		|| !config.textures[3])
		return (FAIL);
	return (SUCCESS);
}

int	mlx_test(t_game *game)
{
	t_player		player;

	game->player = &player;
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d II : Part IV, \
	358/2 days : Remastered : Remake (Cloud version)", false);
	if (game->mlx == NULL)
		return (FAIL);
	game->config.textures[0] = init_rc_texture(game->config.so, game->mlx);
	game->config.textures[2] = init_rc_texture(game->config.no, game->mlx);
	game->config.textures[1] = init_rc_texture(game->config.we, game->mlx);
	game->config.textures[3] = init_rc_texture(game->config.ea, game->mlx);
	game->config.textures[4] = init_rc_texture("img/door_closed.png",
			game->mlx);
	init_player(&player, game->mapinfo);
	if (check_textures_not_corrupted(game->config) == SUCCESS)
	{
		player_loop(game, 'X', 'X');
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
		mlx_loop_hook(game->mlx, input_hook, game);
		mlx_loop(game->mlx);
	}
	free_game_textures(game);
	mlx_terminate(game->mlx);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc == 2)
	{
		init_data_struct(&data);
		if (parse_file(&data, argv[1]) != VALID_FILE)
			return (INVALID_FILE);
		if (mlx_test(&data) == FAIL)
			ft_putstr_fd("cub3d : could not initialze MLX\n", 2);
		free_data_struct(&data, EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("File missing/Too many arguments!\n", STDERR_FILENO);
	}
}
