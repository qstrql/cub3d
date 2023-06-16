/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:52:40 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/08 11:55:13 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	free_mapinfo_struct(t_mapinfo *map)
{
	if (map->map_path)
		free(map->map_path);
	if (map->map)
		free_split_array(&map->map);
	better_free(map);
}

void	free_config_struct(t_config *config)
{
	if (config->no)
		free(config->no);
	if (config->so)
		free(config->so);
	if (config->we)
		free(config->we);
	if (config->ea)
		free(config->ea);
}

void	free_door_anims(t_game *game)
{
	free_rc_texture(game->config.door_anim[0]);
	free_rc_texture(game->config.door_anim[1]);
	free_rc_texture(game->config.door_anim[2]);
	free_rc_texture(game->config.door_anim[3]);
	free_rc_texture(game->config.door_anim[4]);
	free_rc_texture(game->config.door_anim[5]);
	free_rc_texture(game->config.door_anim[6]);
	free_rc_texture(game->config.door_anim[7]);
	free_rc_texture(game->config.door_anim[8]);
}

void	free_game_textures(t_game *game)
{
	free_door_anims(game);
	free_rc_texture(game->config.textures[0]);
	free_rc_texture(game->config.textures[1]);
	free_rc_texture(game->config.textures[2]);
	free_rc_texture(game->config.textures[3]);
	free_rc_texture(game->config.textures[4]);
	mlx_delete_texture(game->player->minimap.textures[0]);
	mlx_delete_texture(game->player->minimap.textures[1]);
	mlx_delete_texture(game->player->minimap.textures[2]);
	mlx_delete_texture(game->player->minimap.textures[3]);
	mlx_delete_texture(game->player->minimap.textures[4]);
	mlx_delete_texture(game->player->minimap.textures[5]);
	mlx_delete_image(game->mlx, game->player->minimap.images[0]);
	mlx_delete_image(game->mlx, game->player->minimap.images[1]);
	mlx_delete_image(game->mlx, game->player->minimap.images[2]);
	mlx_delete_image(game->mlx, game->player->minimap.images[3]);
	mlx_delete_image(game->mlx, game->player->minimap.images[4]);
	mlx_delete_image(game->mlx, game->player->minimap.images[5]);
	free(game->player->minimap.images);
	free(game->player->minimap.textures);
}

int	free_data_struct(t_game *data, int exit_code)
{
	free_config_struct(&data->config);
	free_mapinfo_struct(data->mapinfo);
	if (data->raw_file)
		free_split_array(&data->raw_file);
	return (exit_code);
}
