/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/08 14:32:26 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"


void	mlx_test(t_game *game)
{
	t_player		player;

	game->player = &player;
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d II : Part IV, \
	358/2 days : Remastered : Remake (Cloud version)", false);
	game->config.textures[0] = init_rc_texture(game->config.so, game->mlx);
	game->config.textures[2] = init_rc_texture(game->config.no, game->mlx);
	game->config.textures[1] = init_rc_texture(game->config.we, game->mlx);
	game->config.textures[3] = init_rc_texture(game->config.ea, game->mlx);
	game->config.textures[4] = init_rc_texture("img/door_closed.png",
			game->mlx);
	init_player(&player, game->mlx, game->mapinfo);
	player_loop(game, 'X', 'X', false);
	mlx_loop_hook(game->mlx, input_hook, game);
	mlx_loop(game->mlx);
	free_game_textures(game);
	mlx_terminate(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	data;

	if (argc == 2)
	{
		init_data_struct(&data);
		if (parse_file(&data, argv[1]) != VALID_FILE)
			return (INVALID_FILE);
		debugprint(&data);
		mlx_test(&data);
		free_data_struct(&data, EXIT_SUCCESS);
	}
	else
	{
		ft_putstr_fd("File missing/Too many arguments!\n", STDERR_FILENO);
	}
}
