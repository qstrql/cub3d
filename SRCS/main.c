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

int	str_array_len(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		i++;
	return (i);
}

bool	check_if_struct_filled(t_config *config)
{
	if (config->no == NULL || config->so == NULL || config->we == NULL
		|| config->ea == NULL || config->floor.r == -1
		|| config->ceiling.r == -1)
	{
		return (false);
	}
	else
		return (true);
}

int	check_for_correct_coord(char *coord)
{
	if (ft_strncmp(coord, "NO", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "SO", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "EA", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "WE", 3) == 0)
		return (1);
	else
		return (0);
}

int	check_for_correct_rgb(char *rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]) && rgb[i] != ',')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	fill_floor_rgb(t_config *config, char **tmp)
{
	config->floor.r = ft_atoi(tmp[0]);
	config->floor.g = ft_atoi(tmp[1]);
	config->floor.b = ft_atoi(tmp[2]);
	config->floor.a = 255;
	if (config->floor.r > 255 || config->floor.r < 0)
		return (FAIL);
	if (config->floor.g > 255 || config->floor.g < 0)
		return (FAIL);
	if (config->floor.b > 255 || config->floor.b < 0)
		return (FAIL);
	return (SUCCESS);
}

int	fill_ceiling_rgb(t_config *config, char **tmp)
{
	config->ceiling.r = ft_atoi(tmp[0]);
	config->ceiling.g = ft_atoi(tmp[1]);
	config->ceiling.b = ft_atoi(tmp[2]);
	config->ceiling.a = 255;
	if (config->ceiling.r > 255 || config->ceiling.r < 0)
		return (FAIL);
	if (config->ceiling.g > 255 || config->ceiling.g < 0)
		return (FAIL);
	if (config->ceiling.b > 255 || config->ceiling.b < 0)
		return (FAIL);
	return (SUCCESS);
}

int	get_rbg(t_config *config, char **line)
{
	char	**tmp;
	int		ret;

	ret = FAIL;
	if (check_for_correct_rgb(line[1]) == FAIL)
		return (ret);
	tmp = ft_split(line[1], ',');
	if (str_array_len(tmp) != 3)
	{
		free_split_array(&tmp);
		return (ret);
	}
	if (ft_strncmp(line[0], "F", 2))
		ret = fill_floor_rgb(config, tmp);
	if (ft_strncmp(line[0], "C", 2))
		ret = fill_ceiling_rgb(config, tmp);
	free_split_array(&tmp);
	return (ret);
}

int	get_coord_path(t_config *config, char **line)
{
	if (ft_strncmp(line[0], "NO", 3) == 0 && !config->no)
		config->no = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "SO", 3) == 0 && !config->so)
		config->so = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "EA", 3) == 0 && !config->ea)
		config->ea = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "WE", 3) == 0 && !config->we)
		config->we = ft_strdup(line[1]);
	else
		return (FAIL);
	return (SUCCESS);
}

int	get_texture_rgb(t_config *config, char **line)
{
	int	ret;

	ret = FAIL;
	if (ft_strncmp(line[0], "F", 2) == 0)
		ret = get_rbg(config, line);
	else if (ft_strncmp(line[0], "C", 2) == 0)
		ret = get_rbg(config, line);
	else if (check_for_correct_coord(line[0]) == 1)
		ret = get_coord_path(config, line);
	else
		return (ret);
	return (ret);
}

void	get_map(t_game *data, int i)
{
	int		j;
	int		max_len;

	max_len = 0;
	j = 0;
	while (data->raw_file[i])
	{
		while (str_is_space_only(data->raw_file[i])
			&& i < data->mapinfo->line_count - 1)
			i++;
		if (i >= data->mapinfo->line_count)
			break ;
		data->mapinfo->map[j] = ft_strdup(data->raw_file[i]);
		if ((int)ft_strlen(data->mapinfo->map[j]) > max_len)
			max_len = ft_strlen(data->mapinfo->map[j]);
		data->mapinfo->height++;
		j++;
		i++;
	}
	if (j == 0)
	{
		free(data->mapinfo->map);
		data->mapinfo->map = NULL;
	}
	data->mapinfo->width = max_len;
}

int	get_content(t_game *data, int i)
{
	char	**tmp;
	char	*tmp_trim;

	tmp_trim = ft_strtrim(data->raw_file[i], " \t\n\r\f\v");
	free(data->raw_file[i]);
	data->raw_file[i] = ft_strdup(tmp_trim);
	free(tmp_trim);
	tmp = ft_split(data->raw_file[i], ' ');
	if (check_if_struct_filled(&data->config) == false)
	{
		if (str_array_len(tmp) != 2)
		{
			free_split_array(&tmp);
			return (INVALID_FILE);
		}
	}	
	if (get_texture_rgb(&data->config, tmp) == FAIL)
	{
		free_split_array(&tmp);
		return (INVALID_FILE);
	}
	free_split_array(&tmp);
	return (VALID_FILE);
}

void	remove_map_nl(t_mapinfo *map)
{
	int	i;

	i = map->height - 1;
	while (str_is_space_only(map->map[i]))
	{
		free(map->map[i]);
		map->map[i] = NULL;
		map->height--;
		i--;
	}
}

int	check_file_content(t_game *data)
{
	int		i;

	i = 0;
	while (data->raw_file[i] && check_if_struct_filled(&data->config) == false)
	{
		while (str_is_space_only(data->raw_file[i]))
			i++;
		if (get_content(data, i) == INVALID_FILE)
			return (INVALID_FILE);
		i++;
	}
	if (check_if_struct_filled(&data->config) == false)
		return (INVALID_FILE);
	else
	{
		data->mapinfo->height = 0;
		data->mapinfo->map = ft_calloc(data->mapinfo->line_count,
				sizeof(char *));
		get_map(data, i);
		remove_map_nl(data->mapinfo);
	}
	return (VALID_FILE);
}

int	verify_minimap_textures(void)
{
	if (!file_exist("img/minimap/minimap_wall.png")
		|| !file_exist("img/minimap/map.png")
		|| !file_exist("img/minimap/minimap_player.png")
		|| !file_exist("img/minimap/minimap_ground.png")
		|| !file_exist("img/minimap/minimap_door_closed.png")
		|| !file_exist("img/minimap/minimap_door_open.png"))
		return (FAIL);
	return (SUCCESS);
}

int	verify_texture_path(t_game *data)
{
	if (file_exist(data->config.no) == false)
		return (FAIL);
	if (file_exist(data->config.so) == false)
		return (FAIL);
	if (file_exist(data->config.ea) == false)
		return (FAIL);
	if (file_exist(data->config.we) == false)
		return (FAIL);
	return (SUCCESS);
}

int	verify_map_left(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (j < data->mapinfo->width && data->mapinfo->map[i][j]
			&& ft_isspace(data->mapinfo->map[i][j]))
			j++;
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	verify_map_right(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(data->mapinfo->map[i]) - 1;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (j > 1 && data->mapinfo->map[i][j]
			&& ft_isspace(data->mapinfo->map[i][j]))
			j--;
		if (j <= 1)
			return (FAIL);
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		i++;
		if (i < data->mapinfo->height && data->mapinfo->map[i])
			j = ft_strlen(data->mapinfo->map[i]) - 1;
	}
	return (SUCCESS);
}

int	verify_map_up(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < data->mapinfo->width - 1)
	{
		while (ft_isspace(data->mapinfo->map[i][j]) && data->mapinfo->map[i][j])
		{
			if ((int)ft_strlen(data->mapinfo->map[i + 1]) < j)
				break ;
			i++;
		}
		if (data->mapinfo->map[i][j] != '1' && data->mapinfo->map[i][j])
			return (FAIL);
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	verify_map_down(t_game *data)
{
	int	i;
	int	j;

	i = data->mapinfo->height - 1;
	j = 0;
	while (j < data->mapinfo->width - 1)
	{
		while (i > 1)
		{
			if ((int)ft_strlen(data->mapinfo->map[i]) - 1 < j)
				i--;
			else if (ft_isspace(data->mapinfo->map[i][j]))
				i--;
			else
				break ;
		}
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		i = data->mapinfo->height - 1;
		j++;
	}
	return (SUCCESS);
}

int	verify_player_present(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (j < data->mapinfo->width && data->mapinfo->map[i][j])
		{
			if (ft_strchr("NSWE", data->mapinfo->map[i][j]))
				return (SUCCESS);
			j++;
		}
		j = 0;
		i++;
	}
	return (FAIL);
}

int	verify_map_validity(t_game *data)
{
	if (data->mapinfo->map == NULL)
		return (FAIL);
	if (verify_map_left(data) == FAIL)
	{
		ft_putstr_fd("cub3d: Map is missing wall on left side\n", 2);
		return (FAIL);
	}
	if (verify_map_right(data) == FAIL)
	{
		ft_putstr_fd("cub3d: Map is missing wall on right side\n", 2);
		return (FAIL);
	}
	if (verify_map_up(data) == FAIL)
	{
		ft_putstr_fd("cub3d: Map is missing wall on upper side\n", 2);
		return (FAIL);
	}
	if (verify_map_down(data) == FAIL)
	{
		ft_putstr_fd("cub3d: Map is missing wall on lower side\n", 2);
		return (FAIL);
	}
	if (data->mapinfo->height < 3 || data->mapinfo->width < 3)
		return (FAIL);
	return (SUCCESS);
}

int	verify_map_characters(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height)
	{
		while (data->mapinfo->map[i][j])
		{
			if (ft_strchr("10DWNSE \n\t\r\f\v", data->mapinfo->map[i][j]) == 0)
				return (FAIL);
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	parse_file(t_game *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_game(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		exit_msg(data, WRONG_FILE_CONTENT);
	if (verify_texture_path(data) == FAIL)
		exit_msg(data, WRONG_TEXTURE_PATH);
	if (verify_minimap_textures() == FAIL)
		exit_msg(data, MINIMAP_FILES_MISSING);
	if (verify_map_validity(data) == FAIL)
		exit_msg(data, BAD_MAP);
	if (verify_map_characters(data) == FAIL)
		exit_msg(data, BAD_CHARACTERS);
	return (VALID_FILE);
}

void	ft_printf_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

void	debugprint(t_game *data)
{
	if (data)
	{
		if (data->config.no)
			printf("%s\n", data->config.no);
		if (data->config.so)
			printf("%s\n", data->config.so);
		if (data->config.we)
			printf("%s\n", data->config.we);
		if (data->config.ea)
			printf("%s\n", data->config.ea);
		if (data->config.ceiling.r != -1)
		{
			printf("%d\n", data->config.ceiling.r);
			printf("%d\n", data->config.ceiling.g);
			printf("%d\n", data->config.ceiling.b);
		}
		if (data->config.floor.r != -1)
		{
			printf("%d\n", data->config.floor.r);
			printf("%d\n", data->config.floor.g);
			printf("%d\n", data->config.floor.b);
		}
		if (data->mapinfo->map)
			ft_printf_strs(data->mapinfo->map);
	}
}

void	print_map(t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("map height : %d\n", map->height);
	while (i < map->height)
	{
		while (map->map[i][j])
		{
			printf("%c,", map->map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}

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

void	rotate_player(t_player *player, char rotation)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	if (rotation == 'L')
	{
		player->dir_x = player->dir_x * cos(player->rot_speed)
			- player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed)
			+ player->dir_y * cos(player->rot_speed);
		player->plane_x = player->plane_x * cos(player->rot_speed)
			- player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed)
			+ player->plane_y * cos(player->rot_speed);
		return ;
	}
	player->dir_x = player->dir_x * cos(-player->rot_speed)
		- player->dir_y * sin(-player->rot_speed);
	player->dir_y = old_dir_x * sin(-player->rot_speed)
		+ player->dir_y * cos(-player->rot_speed);
	player->plane_x = player->plane_x * cos(-player->rot_speed)
		- player->plane_y * sin(-player->rot_speed);
	player->plane_y = old_plane_x * sin(-player->rot_speed)
		+ player->plane_y * cos(-player->rot_speed);
}

void	move_player(t_player *player, t_mapinfo *mapinfo, char direction)
{
	if (direction == 'W')
	{
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x + player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x += player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y + player->dir_y * player->move_speed)]))
			player->y += player->dir_y * player->move_speed;
	}
	else if (direction == 'S')
	{
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x - player->dir_x * player->move_speed)] \
		[(int)player->y]))
			player->x -= player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x)] \
		[(int)(player->y - player->dir_y * player->move_speed)]))
			player->y -= player->dir_y * player->move_speed;
	}
}

void	strafe_player(t_player *player, t_mapinfo *mapinfo, char direction)
{
	if (direction == 'A')
	{
		if (ft_strchr("0O", mapinfo->map[(int)player->x] \
		[(int)(player->y - -player->dir_x * player->move_speed)]))
			player->y -= -player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x - player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x -= player->dir_y * player->move_speed;
	}
	else if (direction == 'D')
	{
		if (ft_strchr("0O", mapinfo->map[(int)player->x] \
		[(int)(player->y + -player->dir_x * player->move_speed)]))
			player->y += -player->dir_x * player->move_speed;
		if (ft_strchr("0O", mapinfo->map \
		[(int)(player->x + player->dir_y * player->move_speed)] \
		[(int)(player->y)]))
			player->x += player->dir_y * player->move_speed;
	}	
}

//Top 5 des pires utilisation de la norme
void	player_interact(t_game *game)
{
	if (game->mapinfo->map \
	[(int)(game->player->x + game->player->dir_x * 0.8)] \
	[(int)(game->player->y + game->player->dir_y * 0.8)] == 'D')
		game->mapinfo->map \
		[(int)(game->player->x + game->player->dir_x * 0.8)] \
		[(int)(game->player->y + game->player->dir_y * 0.8)] = 'O';
	else if (game->mapinfo->map \
	[(int)(game->player->x + game->player->dir_x * 0.8)] \
	[(int)(game->player->y + game->player->dir_y * 0.8)] == 'O'
			&& game->mapinfo->map[game->player->map_pos_x] \
			[game->player->map_pos_y] != 'O')
		game->mapinfo->map \
		[(int)(game->player->x + game->player->dir_x * 0.8)] \
		[(int)(game->player->y + game->player->dir_y * 0.8)] = 'D';
}

void	player_loop(t_game *game, char direction, char rotation, bool interact)
{
	if (rotation != 'X')
		rotate_player(game->player, rotation);
	if (direction == 'W' || direction == 'S')
		move_player(game->player, game->mapinfo, direction);
	else if (direction == 'A' || direction == 'D')
		strafe_player(game->player, game->mapinfo, direction);
	if (interact == true)
		player_interact(game);
	game->player->map_pos_x = (int)game->player->x;
	game->player->map_pos_y = (int)game->player->y;
	cast_rays_3d(game->mlx, game->player, game->mapinfo, &game->config);
}

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
