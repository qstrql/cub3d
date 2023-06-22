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

void	free_game_textures(t_game *game)
{
	free_rc_texture(game->config.textures[0]);
	free_rc_texture(game->config.textures[1]);
	free_rc_texture(game->config.textures[2]);
	free_rc_texture(game->config.textures[3]);
	free_rc_texture(game->config.textures[4]);
}
