/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_to_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:45:06 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:45:07 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	reload_map_assets(mlx_t *mlx, t_minimap *minimap)
{
	int	cell_size;

	cell_size = minimap->cell_size;
	if (minimap->images[0]->enabled == true)
	{
		minimap->images[0]->enabled = false;
		mlx_delete_image(mlx, minimap->images[1]);
		mlx_delete_image(mlx, minimap->images[2]);
		mlx_delete_image(mlx, minimap->images[3]);
		mlx_delete_image(mlx, minimap->images[4]);
		mlx_delete_image(mlx, minimap->images[5]);
		return (0);
	}
	minimap->images[1] = mlx_texture_to_image(mlx, minimap->textures[1]);
	minimap->images[2] = mlx_texture_to_image(mlx, minimap->textures[2]);
	minimap->images[3] = mlx_texture_to_image(mlx, minimap->textures[3]);
	minimap->images[4] = mlx_texture_to_image(mlx, minimap->textures[4]);
	minimap->images[5] = mlx_texture_to_image(mlx, minimap->textures[5]);
	mlx_resize_image(minimap->images[1], cell_size, cell_size);
	mlx_resize_image(minimap->images[2], cell_size, cell_size);
	mlx_resize_image(minimap->images[3], cell_size, cell_size);
	mlx_resize_image(minimap->images[4], cell_size, cell_size);
	mlx_resize_image(minimap->images[5], cell_size, cell_size);
	return (1);
}

void	put_tiles_to_screen(t_game *game, int i, int j, int middle)
{
	mlx_t		*mlx;
	t_player	*player;
	int			texture_num;

	mlx = game->mlx;
	player = game->player;
	if (i == player->map_pos_x && j == player->map_pos_y)
		texture_num = 3;
	else if (!ft_strchr("10DO", game->mapinfo->map[i][j]))
		return ;
	else if (game->mapinfo->map[i][j] == '1')
		texture_num = 1;
	else if (game->mapinfo->map[i][j] == 'D')
		texture_num = 4;
	else if (game->mapinfo->map[i][j] == 'O')
		texture_num = 5;
	else
		texture_num = 2;
	mlx_image_to_window(mlx, player->minimap.images[texture_num],
		j * player->minimap.cell_size + middle + 25,
		i * player->minimap.cell_size + 20);
}

void	display_map(t_game *game)
{
	int	i;
	int	j;
	int	middle;

	i = 0;
	j = 0;
	middle = (WIN_WIDTH - game->player->minimap.cell_size
			* game->mapinfo->width) / 2;
	if (!reload_map_assets(game->mlx, &game->player->minimap))
		return ;
	game->player->minimap.images[0]->instances[0].x = middle;
	game->player->minimap.images[0]->enabled = true;
	while (i < game->mapinfo->height)
	{
		while (j < game->mapinfo->width && game->mapinfo->map[i][j])
		{
			put_tiles_to_screen(game, i, j, middle);
			j++;
		}
		j = 0;
		i++;
	}
}
