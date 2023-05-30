/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/30 16:02:27 by mjouot           ###   ########.fr       */
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
	debugprint(data);
	return (VALID_FILE);
}

int	parse_file(t_game *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_program(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
	{
		debugprint(data);
		exit_msg(data, WRONG_FILE_CONTENT);
	}
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

//void	draw_player(mlx_t *mlx int **map);

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

void	draw_map(mlx_t *mlx, t_mapinfo *map, t_sprite wall_sprite)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->height)
	{
		while (j < map->width)
		{
			if (map->map[i][j] != '0')
				mlx_image_to_window(mlx, wall_sprite.img, j * wall_sprite.img->width, i * wall_sprite.img->height);
			j++;
		}
		j = 0;
		i++;
	}
}

void draw_line(void *mlx, int beginX, int beginY, int endX, int endY, int color, int width)
{
	static mlx_image_t *line = NULL;

	if (line != NULL)
		mlx_delete_image(mlx, line);
	line = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
		if (pixelX > WIN_WIDTH || pixelX < 0
		|| pixelY > WIN_HEIGHT || pixelY < 0)
		{
			break ;
		}
		for (int i = 0; i < width; i++)
    		mlx_put_pixel(line, pixelX + i, pixelY, color);
    	pixelX += deltaX;
   		pixelY += deltaY;
    	--pixels;
	}
	mlx_image_to_window(mlx, line, 0, 0);
}

void	draw_player(mlx_t *mlx, t_mapinfo *map, t_player *player, char direction)
{
	if (direction == 'L')
	{
		player->angle -= 0.1;
		if (player->angle < 0)
			player->angle += 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}
	if (direction == 'R')
	{
		player->angle += 0.1;
		if (player->angle > 2 * PI)
			player->angle -= 2 * PI;
		player->dx = cos(player->angle) * 5;
		player->dy = sin(player->angle) * 5;
	}

	int	x_offset;
	int	y_offset;

	if (player->dx < 0)
		x_offset = -20;
	else
		x_offset = 20;
	if (player->dy < 0)
		y_offset = -20;
	else
		y_offset = 20;

	if (direction == 'U')
	{
		if (map->map[(int)(player->y / 64)][(int)((player->x + x_offset) / 64)] == '0')
			player->x += player->dx;
		if (map->map[(int)((player->y + y_offset) / 64)][(int)(player->x / 64)] == '0')
			player->y += player->dy;
	}
	if (direction == 'D')
	{
		if (map->map[(int)(player->y / 64)][(int)((player->x - x_offset) / 64)] == '0')
			player->x -= player->dx;
		if (map->map[(int)((player->y - y_offset) / 64)][(int)(player->x / 64)] == '0')
			player->y -= player->dy;
	}
	player->sprite.img->instances[0].x = player->x;
	player->sprite.img->instances[0].y = player->y;
	//draw_line(mlx, player->x, player->y, player->x + player->dx * 10, player->y + player->dy * 10, 0xFF00FF, 1);
	cast_rays_3d(mlx, player, map);
}

void	input_hook(void *param)
{
	t_game	*game = param;

	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W) || mlx_is_key_down(game->mlx, MLX_KEY_UP))
		draw_player(game->mlx, game->mapinfo, game->player, 'U');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) || mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		draw_player(game->mlx, game->mapinfo, game->player, 'D');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) || mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		draw_player(game->mlx, game->mapinfo, game->player, 'L');
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) || mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		draw_player(game->mlx, game->mapinfo, game->player, 'R');
}

void	free_sprite(t_sprite *sprite, mlx_t *mlx)
{
	mlx_delete_image(mlx, sprite->img);
	mlx_delete_texture(sprite->texture);
}

void	debug_2d_map(t_game *game, t_player *player)
{
	t_sprite	cat;

	cat.texture = mlx_load_png("img/normal_cat.png");
	cat.img = mlx_texture_to_image(game->mlx, cat.texture);
	player->sprite.texture = mlx_load_png("img/dark_cat.png");
	player->sprite.img = mlx_texture_to_image(game->mlx, player->sprite.texture);
	mlx_resize_image(cat.img, 64, 64);
	mlx_resize_image(player->sprite.img, 32, 32);

	draw_map(game->mlx, game->mapinfo, cat);
	mlx_image_to_window(game->mlx, player->sprite.img, 64, 64);
	//free_sprite(&player.sprite, game.mlx);
	//free_sprite(&cat, game.mlx);
}

void 	mlx_test()
{
	t_game		game;
	t_mapinfo	mapinfo;
	t_player	player;

	game.mapinfo = &mapinfo;
	game.player = &player;
	player.x = 256;
	player.y = 256;
	player.angle = 0;
	player.dx = cos(player.angle) * 5;
	player.dy = sin(player.angle) * 5;
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
	game.mapinfo->map[5][5] = '1';
	game.mapinfo->map[5][6] = '1';
	game.mapinfo->map[1][2] = '2';
	game.mapinfo->map[2][2] = '1';
	print_map(game.mapinfo);

	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "aaaaaaa", false);
	debug_2d_map(&game, game.player);
	cast_rays_3d(game.mlx, game.player, game.mapinfo);
	mlx_loop_hook(game.mlx, input_hook, &game);
	mlx_loop(game.mlx);
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
