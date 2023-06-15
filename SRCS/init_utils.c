/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:35:27 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:56:27 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	set_player_rotation(t_player *player, char rotation)
{
	if (rotation == 'N')
	{
		player->dir_x = -1;
		player->plane_y = 0.66;
	}
	else if (rotation == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}
	else if (rotation == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
	else if (rotation == 'E')
	{
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
}

void	set_player_init_pos(t_player *player, t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		while (j < map->width && map->map[i][j])
		{
			if (ft_strchr("NSWE", map->map[i][j]))
			{
				player->x = i + 0.5;
				player->y = j + 0.5;
				player->map_pos_x = j;
				player->map_pos_y = i;
				set_player_rotation(player, map->map[i][j]);
				map->map[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
		j = 0;
	}
	player->x = -1;
}

void	init_minimap_textures(mlx_t *mlx, t_minimap *minimap)
{
	minimap->images = ft_calloc(6, sizeof(mlx_image_t));
	minimap->textures = ft_calloc(6, sizeof(mlx_texture_t));
	minimap->textures[0] = mlx_load_png("img/minimap/map.png");
	minimap->images[0] = mlx_texture_to_image(mlx, minimap->textures[0]);
	minimap->textures[1] = mlx_load_png("img/minimap/minimap_wall.png");
	minimap->images[1] = mlx_texture_to_image(mlx, minimap->textures[1]);
	minimap->textures[2] = mlx_load_png("img/minimap/minimap_ground.png");
	minimap->images[2] = mlx_texture_to_image(mlx, minimap->textures[2]);
	minimap->textures[3] = mlx_load_png("img/minimap/minimap_player.png");
	minimap->images[3] = mlx_texture_to_image(mlx, minimap->textures[3]);
	minimap->textures[4] = mlx_load_png("img/minimap/minimap_door_closed.png");
	minimap->images[4] = mlx_texture_to_image(mlx, minimap->textures[4]);
	minimap->textures[5] = mlx_load_png("img/minimap/minimap_door_open.png");
	minimap->images[5] = mlx_texture_to_image(mlx, minimap->textures[5]);
}

void	init_minimap(t_player *player, mlx_t *mlx, t_mapinfo *map)
{
	init_minimap_textures(mlx, &(player->minimap));
	if (map->width >= map->height)
	{
		player->minimap.cell_size = WIN_WIDTH / map->width / 2;
		mlx_resize_image(player->minimap.images[0],
			player->minimap.cell_size * map->width + 50,
			player->minimap.cell_size * map->width + 50);
	}
	else
	{
		player->minimap.cell_size = WIN_HEIGHT / map->height / 2;
		mlx_resize_image(player->minimap.images[0],
			player->minimap.cell_size * map->height + 50,
			player->minimap.cell_size * map->height + 50);
	}
	mlx_image_to_window(mlx, player->minimap.images[0], 0, 0);
	player->minimap.images[0]->enabled = false;
}

void	init_player(t_player *player, mlx_t *mlx, t_mapinfo *map)
{
	init_minimap(player, mlx, map);
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	set_player_init_pos(player, map);
	player->move_speed = 0.055;
	player->rot_speed = 0.08;
}
