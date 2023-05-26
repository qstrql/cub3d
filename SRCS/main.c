/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/24 19:23:36 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

#define FOV 85
#define WIN_WIDTH FOV * 8
#define WIN_HEIGHT 600
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

int	skip_empty_char(char *line, int j)
{
	int	i;

	i = j;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	return (i);
}

char	*get_textures_path(char *line, int j)
{
	int	i;
	int	len;
	char *texture;

	j = skip_empty_char(line, j);
	len = j;
	while (line[len] && (line[len] != ' ' && line[len] != '\t'))
		len++;
	texture = ft_calloc((len - j + 1), sizeof(char));
	if (texture == NULL)
		return (NULL);
	i = 0;
	while (line[j] && (line[j] != ' ' && line[j] != '\t' && line[j] != '\n'))
		texture[i++] = line[j++];
	j = skip_empty_char(line, j);
	if (line[j] && line[j] != '\n')
		better_free(texture);
	return (texture);
}

int	get_textures_config(t_config *config, char *line, int j)
{
	{
		if (line[j + 2] && ft_isprint(line[j + 2]))
			return (FAIL);
		if (line[j] == 'N' && line[j + 1] == 'O' && !(config->no))
			config->no = get_textures_path(line, j + 2);
		else if (line[j] == 'S' && line[j + 1] == 'O' && !(config->so))
			config->so = get_textures_path(line, j + 2);
		else if (line[j] == 'W' && line[j + 1] == 'E' && !(config->we))
			config->we = get_textures_path(line, j + 2);
		else if (line[j] == 'E' && line[j + 1] == 'A' && !(config->ea))
			config->ea = get_textures_path(line, j + 2);
		else
			return (FAIL);
	}
	return (SUCCESS);
}

int	get_rgb_config(t_config *config, char *line, int j)
{
	if (line[j + 1] && !ft_isprint(line[j + 1]))
		return (FAIL);
	if (!config->floor && line[j] == 'F')
	{
		return (SUCCESS);
	}
	else if (!config->ceiling && line[j] == 'C')
	{
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	get_map_config(t_config *config, char *line, int j)
{
	(void)config;
	(void)line;
	(void)j;
	return (SUCCESS);
}

int	get_config_content(t_game *data, int i, int j)
{
	if (ft_isprint(data->raw_file[i][j]) && !ft_isdigit(data->raw_file[i][j]))
	{
		if (data->raw_file[i][j + 1] && ft_isprint(data->raw_file[i][j + 1] &&
				!ft_isdigit(data->raw_file[i][j + 1])))
		{
			if (get_textures_config(&data->config, data->raw_file[i], j) == FAIL)
				return (FAIL);
		}
		else
		{
			if (get_rgb_config(&data->config, data->raw_file[i], j) == FAIL)
				return (FAIL);
		}
	}
	else if (ft_isdigit(data->raw_file[i][j]))
	{
		if (get_map_config(&data->config, data->raw_file[i], j) == FAIL)
			return (FAIL);
	}
	return (EXIT_SUCCESS);	
}

int	check_file_content(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->mapinfo->line_count < 9)
		return (INVALID_FILE);
	while (data->raw_file[i])
	{
		while (str_is_space_only(data->raw_file[i]))
			i++;
		j = skip_empty_char(data->raw_file[i], j);
		while (data->raw_file[i][j])
		{
			if (get_config_content(data, i, j) == FAIL)
				return (FAIL);
		}
		i++;
	}
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
	printf("%s\n", data->config.no);	
	printf("%s\n", data->config.so);	
	printf("%s\n", data->config.we);	
	printf("%s\n", data->config.ea);	
	printf("%d\n", data->mapinfo->line_count);	
	printf("%s\n", data->mapinfo->map_path);	
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
			if (map->map[i][j] == '1')
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

int		ft_float_to_int(float f)
{
	return ((int)(f - fmod(f, 1)));
}

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

/*
void	draw_3d_image(mlx_t *mlx, int ray, float dist)
{


	while (pixel_pos < WINDOW_WIDTH)
	{
		for (int i = 0; i < WINDOW_HEIGHT; i++)
			mlx_put_pixel(window, pixel_pos, i, 0x00FF00FF)
		pixel_pos++;
	}
	mlx_image_to_window(mlx, window, 0, 0);
}
*/

void	cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map)
{
	int	ray;
	int	map_x;
	int	map_y;
	int	dof;

	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	xo;
	float	yo;

	float	dist_h;
	float	dist_v;
	float	hit_x_hor;
	float	hit_y_hor;
	float	hit_x_ver;
	float	hit_y_ver;
	float	dist_real;

	int		cast_color;
	static mlx_image_t	*window = NULL;
	if (window != NULL)
			mlx_delete_image(mlx, window);
	window = mlx_new_image(mlx, WIN_WIDTH * 2, WIN_HEIGHT * 2);
	dist_h = 10000000;
	hit_x_hor = player->x;
	hit_y_hor = player->y;
	//ray_angle = player->angle;
	ray_angle = player->angle - (RAD1 * 30);
	if (ray_angle < 0)
		ray_angle += 2 * PI;
	if (ray_angle > 2 * PI)
		ray_angle = -2 * PI;
	ray = 0;
	while (ray < FOV)
	{
		//La majorité du code c'est des calculs plutot inexplicables mais je vais essayer d'au moins expliquer leur but
		//------------------------- Horizontal -------------------------
		dof = 0;
		float aTan = -1 / tan(ray_angle);
		//Cast du ray, si son angle dépasse un certain angle, on le reset pour le remttre bien
		//Up (par rapport a l'axe horizontal, donc gauche pour nous)
		if (ray_angle > PI)
		{
			ray_y = (((int)player->y / 64) * 64) - 0.0001;
			ray_x = (player->y - ray_y) * aTan + player->x;
			yo = -64;
			xo = -yo*aTan;
		}
		//Down (par rapport a l'axe horizontal, donc droite pour nous)
		if (ray_angle < PI)
		{
			ray_y = (((int)player->y / 64) * 64) + 64;
			ray_x = (player->y - ray_y) * aTan + player->x;
			yo = 64;
			xo = -yo*aTan;
		}
		//Si on regarde directement en bas ou en haut, on ne peut evidemment rien hit horizontalement, donc on met le dof directement a 8 
		//Left/Right (par rapport a l'axe horizontal, donc haut/bas pour nous)
		if (ray_angle == 0 || ray_angle == PI * 2)
		{
			ray_x = player->x;
			ray_y = player->y;
			dof = 8;
		}
		//Check de collisions
		//Dof est le nombre de fois ou on va iterer pour check une collision, le check n'est fait que a chaque X de tile
		//Ex : Nos tiles sont de 64 pixels, donc on va check tt les 64 pixels, aux extrémités de nos cases.
		while (dof < 8)
		{
			//Bitshift de 6 = Division par 64, juste plus efficace
			map_x = (int)(ray_x)>>6;
			map_y = (int)(ray_y)>>6;
			if (map_x >= 0 && map_y >= 0)
			{
				//Si on a en effet une collision, on recupere le x et y du ray, ainsi que la distance de la collision par rapport au joueur
				if (map_x < map->width && map_y < map->height && map->map[map_y][map_x] == '1')
				{
					//printf("hitting [%d][%d]\n", map_y, map_x);
					hit_x_hor = ray_x;
					hit_y_hor = ray_y;
					dist_h = dist(player->x, player->y, hit_x_hor, hit_y_hor);
					dof = 8;
				}
				else
				{
					ray_x += xo;
					ray_y += yo;
					dof += 1; //next step
				}
			}
			else
			{
				ray_x += xo;
				ray_y += yo;
				dof += 1; //next step
			}
		}
		if (ray_x > (float)INT_MAX - 1|| ray_x < INT_MIN)
			ray_x = player->x;
		if (ray_y > (float)INT_MAX - 1|| ray_y < INT_MIN)
			ray_y = player->y;

		//------------------------- Vertical -------------------------
		dof = 0;
		float nTan = -tan(ray_angle);
		dist_v = 10000000;
		hit_x_ver = player->x;
		hit_y_ver = player->y;
		//left
		//Cast du ray, si son angle dépasse un certain angle, on le reset pour le remttre bien
		//Left (par rapport a l'axe vertical)
		if (ray_angle > PI2 && ray_angle < PI3)
		{
			ray_x = (((int)player->x / 64) * 64) - 0.0001;
			ray_y = (player->x - ray_x) * nTan + player->y;
			xo = -64;
			yo = -xo*nTan;
		}
		//Right (par rapport a l'axe vertical)
		if (ray_angle < PI2 || ray_angle > PI3)
		{
			ray_x = (((int)player->x / 64) * 64) + 64;
			ray_y = (player->x - ray_x) * nTan + player->y;
			xo = 64;
			yo = -xo*nTan;
		}
		//Si on regarde directement en bas ou en haut, on ne peut evidemment rien hit horizontalement, donc on met le dof directement a 8
		//Up/Down
		if (ray_angle == 0 || ray_angle == PI * 2)
		{
			ray_x = player->x;
			ray_y = player->y;
			dof = 8;
		}
		//Check de collisions
		//Dof est le nombre de fois ou on va iterer pour check une collision, le check n'est fait que a chaque X de tile
		//Ex : Nos tiles sont de 64 pixels, donc on va check tt les 64 pixels, aux extrémités de nos cases.
		while (dof < 8)
		{
			//Bitshift de 6 = Division par 64, juste plus rapide
			map_x = (int)(ray_x)>>6;
			map_y = (int)(ray_y)>>6;
			if (map_x >= 0 && map_y >= 0)
			{
				//Si on a en effet une collision, on recupere le x et y de ray, ainsi que la distance de la collision par rapport au joueur
				if (map_x < map->width && map_y < map->height && map->map[map_y][map_x] == '1')
				{
					//printf("hitting [%d][%d]\n", map_y, map_x);
					hit_x_ver = ray_x;
					hit_y_ver = ray_y;
					dist_v = dist(player->x, player->y, hit_x_ver, hit_y_ver);
					dof = 8;
				}
				else
				{
					ray_x += xo;
					ray_y += yo;
					dof += 1; //next step
				}
			}
			else
			{
				ray_x += xo;
				ray_y += yo;
				dof += 1; //next step
			}
		}
		if (ray_x > (float)INT_MAX - 1|| ray_x < INT_MIN)
			ray_x = player->x;
		if (ray_y > (float)INT_MAX - 1|| ray_y < INT_MIN)
			ray_y = player->y;
		
		//Des deux distance récupérées, on regarde laquelle et la plus courte et on draw celle la
		if (dist_v < dist_h)
		{
			ray_x = hit_x_ver;
			ray_y = hit_y_ver;
			dist_real = dist_v;
			cast_color = 0xFF0000FF;
		}
		else
		{
			ray_x = hit_x_hor;
			ray_y = hit_y_hor;
			dist_real = dist_h;
			cast_color = 0xAB0213FF;
		}
		(void)mlx;
		//draw_line(mlx, (ft_float_to_int(player->x)) + 16, ft_float_to_int(player->y), ft_float_to_int(ray_x), ft_float_to_int(ray_y), 0x00FF00FF, 1);
		float	line_height;
		float	line_offset;
		float	cor_angle;

		cor_angle = player->angle - ray_angle;
		if (cor_angle < 0)
			cor_angle += 2 * PI;
		if (cor_angle > 2 * PI)
			ray_angle = -2 * PI;
		dist_real = dist_real * cos(cor_angle);
		line_height = (64 * WIN_HEIGHT) / dist_real;
		if (line_height > WIN_HEIGHT)
			line_height = WIN_HEIGHT;
		line_offset = (WIN_HEIGHT / 2) - (line_height / 2);
		printf("line off : %f, line height : %f\n", line_offset, line_height);
		for (int i = 0; i < 8; i++)
		{
			for (int j = line_offset; j < line_height + line_offset; j++)
			{
				//printf("drawing %dx%d\n", i, j);
				mlx_put_pixel(window, (ray * 8) + i, j, cast_color);
			}
		}
		ray++;
		ray_angle += RAD1;
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		if (ray_angle > 2 * PI)
			ray_angle = -2 * PI;
		
	}
	mlx_image_to_window(mlx, window, 0, 0);
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
	if (direction == 'U')
	{
		player->x += player->dx;
		player->y += player->dy;
	}
	if (direction == 'D')
	{
		player->x -= player->dx;
		player->y -= player->dy;
	}
	//player->sprite.img->instances[0].x = player->x;
	//player->sprite.img->instances[0].y = player->y;
	//draw_line(mlx, player->x, player->y, player->x + player->dx * 10, player->y + player->dy * 10, 0xFF00FF);
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

void 	mlx_test()
{
	t_game		game;
	t_mapinfo	mapinfo;
	t_player	player;
	t_sprite	cat;

	game.mapinfo = &mapinfo;
	game.player = &player;
	player.x = 64;
	player.y = 64;
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
	game.mapinfo->map[1][2] = '1';
	game.mapinfo->map[2][2] = '1';
	print_map(game.mapinfo);

	game.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "aaaaaaa", false);
	cat.texture = mlx_load_png("img/normal_cat.png");
	cat.img = mlx_texture_to_image(game.mlx, cat.texture);
	player.sprite.texture = mlx_load_png("img/dark_cat.png");
	player.sprite.img = mlx_texture_to_image(game.mlx, player.sprite.texture);
	mlx_resize_image(cat.img, 64, 64);
	mlx_resize_image(player.sprite.img, 32, 32);

	//draw_map(game.mlx, game.mapinfo, cat);
	//mlx_image_to_window(game.mlx, player.sprite.img, 64, 64);
	mlx_loop_hook(game.mlx, input_hook, &game);
	mlx_loop(game.mlx);
	free_sprite(&player.sprite, game.mlx);
	free_sprite(&cat, game.mlx);
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
		printf("ouai\n");
		mlx_test();
	}
}
