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

void	init_door_animation_textures(t_game *game)
{
	game->config.door_anim[0] = init_rc_texture("img/door_anim/door_anim0.png",
			game->mlx);
	game->config.door_anim[1] = init_rc_texture("img/door_anim/door_anim1.png",
			game->mlx);
	game->config.door_anim[2] = init_rc_texture("img/door_anim/door_anim2.png",
			game->mlx);
	game->config.door_anim[3] = init_rc_texture("img/door_anim/door_anim3.png",
			game->mlx);
	game->config.door_anim[4] = init_rc_texture("img/door_anim/door_anim4.png",
			game->mlx);
	game->config.door_anim[5] = init_rc_texture("img/door_anim/door_anim5.png",
			game->mlx);
	game->config.door_anim[6] = init_rc_texture("img/door_anim/door_anim6.png",
			game->mlx);
	game->config.door_anim[7] = init_rc_texture("img/door_anim/door_anim7.png",
			game->mlx);
	game->config.door_anim[8] = init_rc_texture("img/door_anim/door_anim8.png",
			game->mlx);
}

int	check_textures_not_corrupted(t_config config, t_minimap minimap)
{
	if (!config.textures[0] || !config.textures[1] || !config.textures[2]
		|| !config.textures[3] || !config.door_anim[0] || !config.door_anim[1]
		|| !config.door_anim[2] || !config.door_anim[3] || !config.door_anim[4]
		|| !config.door_anim[5] || !config.door_anim[6] || !config.door_anim[7]
		|| !config.door_anim[8] || !minimap.textures[0]
		|| !minimap.textures[1] || !minimap.textures[2]
		|| !minimap.textures[3] || !minimap.textures[4]
		|| !minimap.textures[5])
		return (FAIL);
	return (SUCCESS);
}

int	mlx_test(t_game *game)
{
	t_player		player;

	game->player = &player;
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d II : Part IV, \
	358/2 days : Remastered : Remake (Cloud version (Bonus))", false);
	if (game->mlx == NULL)
		return (FAIL);
	game->config.textures[0] = init_rc_texture(game->config.so, game->mlx);
	game->config.textures[2] = init_rc_texture(game->config.no, game->mlx);
	game->config.textures[1] = init_rc_texture(game->config.we, game->mlx);
	game->config.textures[3] = init_rc_texture(game->config.ea, game->mlx);
	game->config.textures[4] = init_rc_texture("img/door_closed.png",
			game->mlx);
	init_door_animation_textures(game);
	init_player(&player, game->mlx, game->mapinfo);
	if (check_textures_not_corrupted(game->config, player.minimap) == SUCCESS)
	{
		player_loop(game, 'X', 'X', false);
		mlx_set_cursor_mode(game->mlx, MLX_MOUSE_DISABLED);
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
