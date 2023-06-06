/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/06 12:43:14 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

//For autocomplete
/*-----------------------------------------------------------------------------*/
mlx_t* mlx_init(int32_t width, int32_t height, const char* title, bool resize);
void mlx_set_setting(mlx_settings_t setting, int32_t value);
void mlx_close_window(mlx_t* mlx);
void mlx_loop(mlx_t* mlx);
void mlx_set_icon(mlx_t* mlx, mlx_texture_t* image);
void mlx_terminate(mlx_t* mlx);
double mlx_get_time(void);
void mlx_focus(mlx_t* mlx);
void mlx_get_monitor_size(int32_t index, int32_t* width, int32_t* height);
void mlx_set_window_pos(mlx_t* mlx, int32_t xpos, int32_t ypos);
void mlx_get_window_pos(mlx_t* mlx, int32_t* xpos, int32_t* ypos);
void mlx_set_window_size(mlx_t* mlx, int32_t new_width, int32_t new_height);
void mlx_set_window_limit(mlx_t* mlx, int32_t min_w, int32_t min_h, int32_t max_w, int32_t max_h);
void mlx_set_window_title(mlx_t* mlx, const char* title);
bool mlx_is_key_down(mlx_t* mlx, keys_t key);
bool mlx_is_mouse_down(mlx_t* mlx, mouse_key_t key);
void mlx_get_mouse_pos(mlx_t* mlx, int32_t* x, int32_t* y);
void mlx_set_mouse_pos(mlx_t* mlx, int32_t x, int32_t y);
void mlx_set_cursor_mode(mlx_t* mlx, mouse_mode_t mode);
mlx_win_cursor_t* mlx_create_std_cursor(cursor_t type);
mlx_win_cursor_t* mlx_create_cursor(mlx_texture_t* texture);
void mlx_destroy_cursor(mlx_win_cursor_t* cursor);
void mlx_set_cursor(mlx_t* mlx, mlx_win_cursor_t* cursor);
void mlx_scroll_hook(mlx_t* mlx, mlx_scrollfunc func, void* param);
void mlx_mouse_hook(mlx_t* mlx, mlx_mousefunc func, void* param);
void mlx_cursor_hook(mlx_t* mlx, mlx_cursorfunc func, void* param);
void mlx_key_hook(mlx_t* mlx, mlx_keyfunc func, void* param);
void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);
void mlx_resize_hook(mlx_t* mlx, mlx_resizefunc func, void* param);
bool mlx_loop_hook(mlx_t* mlx, void (*f)(void*), void* param);
mlx_texture_t* mlx_load_png(const char* path);
xpm_t* mlx_load_xpm42(const char* path);
void mlx_delete_texture(mlx_texture_t* texture);
void mlx_delete_xpm42(xpm_t* xpm);
mlx_image_t* mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);
mlx_image_t* mlx_new_image(mlx_t* mlx, uint32_t width, uint32_t height);
int32_t mlx_image_to_window(mlx_t* mlx, mlx_image_t* img, int32_t x, int32_t y);
void mlx_delete_image(mlx_t* mlx, mlx_image_t* image);
bool mlx_resize_image(mlx_image_t* img, uint32_t nwidth, uint32_t nheight);
void mlx_set_instance_depth(mlx_instance_t* instance, int32_t zdepth);
mlx_image_t* mlx_put_string(mlx_t* mlx, const char* str, int32_t x, int32_t y);
const mlx_texture_t* mlx_get_font(void);
int32_t mlx_get_texoffset(char c);
/*-----------------------------------------------------------------------------*/

bool check_if_struct_filled(t_config *config) 
{
	if (config->no == NULL || config->so == NULL || config->we == NULL ||
		config->ea == NULL || config->floor == NULL || config->ceiling == NULL)
	{
        return false;
	}
	else
	{
        return true;
	}
}

int check_for_correct_coord(char *coord)
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
	config->floor = malloc(3 * sizeof(int));
	config->floor[RED] = ft_atoi(tmp[0]);
	config->floor[GREEN] = ft_atoi(tmp[1]);
	config->floor[BLUE] = ft_atoi(tmp[2]);
	if (config->floor[RED] > 255 ||  config->floor[RED] < 0)
		return (FAIL);
	if (config->floor[GREEN] > 255 ||  config->floor[GREEN] < 0)
		return (FAIL);
	if (config->floor[BLUE] > 255 ||  config->floor[BLUE] < 0)
		return (FAIL);
	return (SUCCESS);
}

int fill_ceiling_rgb(t_config *config, char **tmp)
{
	config->ceiling = malloc(3 * sizeof(int));
	config->ceiling[RED] = ft_atoi(tmp[0]);
	config->ceiling[GREEN] = ft_atoi(tmp[1]);
	config->ceiling[BLUE] = ft_atoi(tmp[2]);
	if (config->ceiling[RED] > 255 ||  config->ceiling[RED] < 0)
		return (FAIL);
	if (config->ceiling[GREEN] > 255 ||  config->ceiling[GREEN] < 0)
		return (FAIL);
	if (config->ceiling[BLUE] > 255 ||  config->ceiling[BLUE] < 0)
		return (FAIL);
	return (SUCCESS);
}

int	get_rbg(t_config *config, char **line)
{
	char **tmp;
	int	ret;

	ret = FAIL;
	if (check_for_correct_rgb(line[1]) == FAIL)
		return (ret);
	tmp = ft_split(line[1], ',');
	if (tmp[3] || !tmp[2])
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

int get_texture_rgb(t_config *config, char **line)
{
	int ret;

	ret = FAIL;
	if (ft_strncmp(line[0], "F", 2) == 0 || ft_strncmp(line[0], "C", 2) == 0)
		ret = get_rbg(config, line);
	else if (check_for_correct_coord(line[0]) == 1)
		ret = get_coord_path(config, line);
	else
		return (ret);
	return (ret);	
}

void get_map(t_game *data, int i)
{
	
}

int	check_file_content(t_game *data)
{
	int	i;
	char **tmp;

	i = 0;
	while (data->raw_file[i])
	{
		while (str_is_space_only(data->raw_file[i]))
			i++;
		data->raw_file[i] = ft_strtrim(data->raw_file[i], " \t\n\r\f\v");
		tmp = ft_split(data->raw_file[i], ' ');
		if (check_if_struct_filled(&data->config) == false)
			if (tmp[2] || !tmp[1])
				return (INVALID_FILE);
		if (get_texture_rgb(&data->config, tmp) == FAIL)
		{
			free_split_array(&tmp);
			return (INVALID_FILE);
		}
		free_split_array(&tmp);
		i++;
	}
	if (check_if_struct_filled(&data->config) == false)
		return (INVALID_FILE);
	else
		get_map(data, i);
	debugprint(data);
	return (VALID_FILE);
}

int	parse_file(t_game *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_program(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		exit_msg(data, WRONG_FILE_CONTENT);
	return (VALID_FILE);
}

void	debugprint(t_game *data)
{
	if (data) {
		if (data->config.no) {
			printf("%s\n", data->config.no);
		}
		if (data->config.so) {
			printf("%s\n", data->config.so);
		}
		if (data->config.we) {
			printf("%s\n", data->config.we);
		}
		if (data->config.ea) {
			printf("%s\n", data->config.ea);
		}
		if (data->config.ceiling) {
			printf("%d\n", data->config.ceiling[RED]);
			printf("%d\n", data->config.ceiling[GREEN]);
			printf("%d\n", data->config.ceiling[BLUE]);
		}
		if (data->config.floor) {
			printf("%d\n", data->config.floor[RED]);
			printf("%d\n", data->config.floor[GREEN]);
			printf("%d\n", data->config.floor[BLUE]);
		}
	}
}

void	print_map(t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		while (map->map[i][j])
		{
			printf("%c, ", map->map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}

void	rotate_player(t_game *game, char rotation)
{
	if (rotation == 'L')
	{
		double	oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(game->player->rot_speed) - game->player->dir_y * sin(game->player->rot_speed);
		game->player->dir_y = oldDirX * sin(game->player->rot_speed) + game->player->dir_y * cos(game->player->rot_speed);
		double	oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(game->player->rot_speed) - game->player->plane_y * sin(game->player->rot_speed);
		game->player->plane_y = oldPlaneX * sin(game->player->rot_speed) + game->player->plane_y * cos(game->player->rot_speed);
	}
	else if (rotation == 'R')
	{
		double	oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-game->player->rot_speed) - game->player->dir_y * sin(-game->player->rot_speed);
		game->player->dir_y = oldDirX * sin(-game->player->rot_speed) + game->player->dir_y * cos(-game->player->rot_speed);
		double	oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-game->player->rot_speed) - game->player->plane_y * sin(-game->player->rot_speed);
		game->player->plane_y = oldPlaneX * sin(-game->player->rot_speed) + game->player->plane_y * cos(-game->player->rot_speed);
	}
}

void	move_player(t_game *game, char direction)
{
	if (direction == 'W')
	{
		if (game->mapinfo->map[(int)(game->player->x + game->player->dir_x * game->player->move_speed)][(int)game->player->y] == '0')
			game->player->x += game->player->dir_x * game->player->move_speed;
		if (game->mapinfo->map[(int)(game->player->x)][(int)(game->player->y + game->player->dir_y * game->player->move_speed)] == '0')
			game->player->y += game->player->dir_y * game->player->move_speed;
	}
	else if (direction == 'S')
	{
		if (game->mapinfo->map[(int)(game->player->x - game->player->dir_x * game->player->move_speed)][(int)game->player->y] == '0')
			game->player->x -= game->player->dir_x * game->player->move_speed;
		if (game->mapinfo->map[(int)(game->player->x)][(int)(game->player->y - game->player->dir_y * game->player->move_speed)] == '0')
			game->player->y -= game->player->dir_y * game->player->move_speed;
	}
}

void	strafe_player(t_game *game, char direction)
{
	if (direction == 'A')
	{
		if (game->mapinfo->map[(int)(game->player->y - -game->player->dir_x * game->player->move_speed)][(int)game->player->x] == '0')
			game->player->y -= -game->player->dir_x * game->player->move_speed;
		if (game->mapinfo->map[(int)(game->player->y)][(int)(game->player->x - game->player->dir_y * game->player->move_speed)] == '0')
			game->player->x -= game->player->dir_y * game->player->move_speed;
	}
	else if (direction == 'D')
	{
		if (game->mapinfo->map[(int)(game->player->y + -game->player->dir_x * game->player->move_speed)][(int)game->player->x] == '0')
			game->player->y += -game->player->dir_x * game->player->move_speed;
		if (game->mapinfo->map[(int)(game->player->y)][(int)(game->player->x + game->player->dir_y * game->player->move_speed)] == '0')
			game->player->x += game->player->dir_y * game->player->move_speed;
	}
}

void	display_map(mlx_t *mlx, t_player player, t_mapinfo map)
{
	int i;
	int j;
	int middle;

	i = 0;
	j = 0;
	middle = (WIN_WIDTH - player.minimap.cell_size * map.width) / 2;
	if (player.minimap.images[0]->enabled == true)
	{
		player.minimap.images[0]->enabled = false;
		mlx_delete_image(mlx, player.minimap.images[1]);
		mlx_delete_image(mlx, player.minimap.images[2]);
		mlx_delete_image(mlx, player.minimap.images[3]);
		return ;
	}
	player.minimap.images[1] = mlx_texture_to_image(mlx, player.minimap.textures[1]);
	player.minimap.images[2] = mlx_texture_to_image(mlx, player.minimap.textures[2]);
	player.minimap.images[3] = mlx_texture_to_image(mlx, player.minimap.textures[3]);
	mlx_resize_image(player.minimap.images[1], player.minimap.cell_size, player.minimap.cell_size);
	mlx_resize_image(player.minimap.images[2], player.minimap.cell_size, player.minimap.cell_size);
	mlx_resize_image(player.minimap.images[3], player.minimap.cell_size, player.minimap.cell_size);
	player.minimap.images[0]->instances[0].x = middle;
	player.minimap.images[0]->enabled = true;
	while (i < map.height)
	{
		while (j < map.width)
		{
			if (i == player.map_pos_x && j == player.map_pos_y)
				mlx_image_to_window(mlx, player.minimap.images[3], j * player.minimap.cell_size + middle + 25, i * player.minimap.cell_size + 20);
			else if (map.map[i][j] == '1')
				mlx_image_to_window(mlx, player.minimap.images[1], j * player.minimap.cell_size + middle + 25, i * player.minimap.cell_size + 20);
			else if (map.map[i][j] == '0')
				mlx_image_to_window(mlx, player.minimap.images[2], j * player.minimap.cell_size + middle + 25, i * player.minimap.cell_size + 20);
			j++;
		}
		j = 0;
		i++;
	}
}

void	player_loop(t_game *game, char direction, char rotation)
{
	if (rotation != 'X')
		rotate_player(game, rotation);
	if (direction == 'W' || direction == 'S')
		move_player(game, direction);
	else if (direction == 'A' || direction == 'D')
		strafe_player(game, direction);
	game->player->map_pos_x = (int)game->player->x;
	game->player->map_pos_y = (int)game->player->y;
	cast_rays_3d(game->mlx, game->player, game->mapinfo, game->textures);
}

void	input_hook(void *param)
{
	t_game	*game = param;
	char	dir;
	char	rot;

	dir = 'X';
	rot = 'X';
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_M) && !game->player->minimap.images[0]->enabled)
		display_map(game->mlx, *game->player, *game->mapinfo);
	else if (mlx_is_key_down(game->mlx, MLX_KEY_N) && game->player->minimap.images[0]->enabled)
		display_map(game->mlx, *game->player, *game->mapinfo);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) && !game->player->minimap.images[0]->enabled)
		dir = 'W';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) && !game->player->minimap.images[0]->enabled)
		dir = 'S';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) && !game->player->minimap.images[0]->enabled)
		dir = 'A';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) && !game->player->minimap.images[0]->enabled)
		dir = 'D';
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) && !game->player->minimap.images[0]->enabled)
		rot = 'L';
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) && !game->player->minimap.images[0]->enabled)
		rot = 'R';
	if (dir != 'X' || rot != 'X')
		player_loop(game, dir, rot);
}

void	init_player(t_player *player, mlx_t *mlx, t_mapinfo map)
{
	player->minimap.images = ft_calloc(4, sizeof(mlx_image_t));
	player->minimap.textures = ft_calloc(4, sizeof(mlx_texture_t));
	player->minimap.textures[0] = mlx_load_png("img/map.png");
	player->minimap.images[0] = mlx_texture_to_image(mlx, player->minimap.textures[0]);
	player->minimap.textures[1] = mlx_load_png("img/minimap_wall.png");
	player->minimap.images[1] = mlx_texture_to_image(mlx, player->minimap.textures[1]);
	player->minimap.textures[2] = mlx_load_png("img/minimap_ground.png");
	player->minimap.images[2] = mlx_texture_to_image(mlx, player->minimap.textures[2]);
	player->minimap.textures[3] = mlx_load_png("img/minimap_player.png");
	player->minimap.images[3] = mlx_texture_to_image(mlx, player->minimap.textures[3]);
	if (map.width >= map.height)
	{
		player->minimap.cell_size = WIN_WIDTH / map.width / 2;
		mlx_resize_image(player->minimap.images[0], player->minimap.cell_size * map.width + 50, player->minimap.cell_size * map.width + 50);
	}
	else
	{
		player->minimap.cell_size = WIN_HEIGHT / map.height / 2;
		mlx_resize_image(player->minimap.images[0], player->minimap.cell_size * map.height + 50, player->minimap.cell_size * map.height + 50);
	}
	mlx_image_to_window(mlx, player->minimap.images[0], 0, 0);
	player->minimap.images[0]->enabled = false;
	player->dir_x = -1;
	player->dir_y = 0;
	player->x = 5;
	player->y = 4;
	player->plane_x = 0;
	player->plane_y = 0.66;
	player->move_speed = 0.07;
	player->rot_speed = 0.08;
}

void 	mlx_test()
{
	t_game			game;
	t_mapinfo		mapinfo;
	t_player		player;

	game.mapinfo = &mapinfo;
	game.player = &player;
	game.mapinfo->map = ft_calloc(sizeof(char *), 11);
	game.mapinfo->height = 10;
	game.mapinfo->width = 10;
	for (int i = 0; i < 10; i++)
	{
		game.mapinfo->map[i] = ft_calloc(sizeof(char), 11);
		if (i == 0 || i == 9)
		{
			for (int j = 0; j < 10; j++)
				game.mapinfo->map[i][j] = '1';
		}
		else
		{
			game.mapinfo->map[i][0] = '1';
			game.mapinfo->map[i][9] = '1';
			for (int j = 1; j < 9; j++)
				game.mapinfo->map[i][j] = '0';
		}
	}
	game.mapinfo->map[6][7] = '1';
	game.mapinfo->map[6][6] = '1';
	game.mapinfo->map[7][7] = '1';
	game.mapinfo->map[2][1] = '1';
	game.mapinfo->map[2][2] = '1';
	print_map(game.mapinfo);

	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3d II : Part IV, 358/2 days : Remastered : Remake (Cloud version)", false);
	game.textures[0] = init_rc_texture("img/normal_cat.png", game.mlx);
	game.textures[1] = init_rc_texture("img/Untitled.png", game.mlx);
	game.textures[2] = init_rc_texture("img/wallpaper.png", game.mlx);
	game.textures[3] = init_rc_texture("img/dark_cat.png", game.mlx);
	init_player(&player, game.mlx, *game.mapinfo);
	//cast_rays_3d(game.mlx, game.player, game.mapinfo, game.textures);
	player_loop(&game, 'X', 'X');
	mlx_loop_hook(game.mlx, input_hook, &game);
	mlx_loop(game.mlx);
	free_split_array(&game.mapinfo->map);
	free_rc_texture(game.textures[0]);
	free_rc_texture(game.textures[1]);
	free_rc_texture(game.textures[2]);
	free_rc_texture(game.textures[3]);
	mlx_delete_texture(game.player->minimap.textures[0]);
	mlx_delete_texture(game.player->minimap.textures[1]);
	mlx_delete_texture(game.player->minimap.textures[2]);
	mlx_delete_texture(game.player->minimap.textures[3]);
	mlx_delete_image(game.mlx, player.minimap.images[0]);
	mlx_delete_image(game.mlx, player.minimap.images[1]);
	mlx_delete_image(game.mlx, player.minimap.images[2]);
	mlx_delete_image(game.mlx, player.minimap.images[3]);
	free(game.player->minimap.images);
	free(game.player->minimap.textures);
	mlx_terminate(game.mlx);
}

int	main(int argc, char **argv)
{
	t_game	data;

	//if (argc != 2)
	//	return (error_msg(USAGE, EXIT_FAILURE));
	if (argc == 2)
	{
		init_data_struct(&data);
		if (parse_file(&data, argv[1]) != VALID_FILE)
			return (INVALID_FILE);
		debugprint(&data);
		free_data_struct(&data, EXIT_SUCCESS);
	}
	else
	{
		mlx_test();
	}
}
