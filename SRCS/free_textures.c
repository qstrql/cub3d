/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 19:29:10 by lbertaux          #+#    #+#             */
/*   Updated: 2023/06/22 19:29:11 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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

void	free_minimap_textures(mlx_t *mlx, t_minimap *minimap)
{
	if (minimap->textures[0])
		mlx_delete_texture(minimap->textures[0]);
	if (minimap->textures[1])
		mlx_delete_texture(minimap->textures[1]);
	if (minimap->textures[2])
		mlx_delete_texture(minimap->textures[2]);
	if (minimap->textures[3])
		mlx_delete_texture(minimap->textures[3]);
	if (minimap->textures[4])
		mlx_delete_texture(minimap->textures[4]);
	if (minimap->textures[5])
		mlx_delete_texture(minimap->textures[5]);
	if (!(!minimap->textures[0]
			|| !minimap->textures[1] || !minimap->textures[2]
			|| !minimap->textures[3] || !minimap->textures[4]
			|| !minimap->textures[5]))
	{
		mlx_delete_image(mlx, minimap->images[0]);
		mlx_delete_image(mlx, minimap->images[1]);
		mlx_delete_image(mlx, minimap->images[2]);
		mlx_delete_image(mlx, minimap->images[3]);
		mlx_delete_image(mlx, minimap->images[4]);
		mlx_delete_image(mlx, minimap->images[5]);
	}
}

void	free_game_textures(t_game *game)
{
	free_door_anims(game);
	free_rc_texture(game->config.textures[0]);
	free_rc_texture(game->config.textures[1]);
	free_rc_texture(game->config.textures[2]);
	free_rc_texture(game->config.textures[3]);
	free_rc_texture(game->config.textures[4]);
	free_minimap_textures(game->mlx, &game->player->minimap);
	free(game->player->minimap.images);
	free(game->player->minimap.textures);
}
