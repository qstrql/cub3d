/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/06 00:11:03 by mjouot           ###   ########.fr       */
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

int	get_config_content(t_data *data, int i, int j)
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

int	check_file_content(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (data->map.line_count < 9)
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

int	parse_file(t_data *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_program(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		exit_msg(data, WRONG_FILE_CONTENT);
	return (VALID_FILE);
}

void	debugprint(t_data *data)
{
	printf("%s\n", data->config.no);	
	printf("%s\n", data->config.so);	
	printf("%s\n", data->config.we);	
	printf("%s\n", data->config.ea);	
	printf("%d\n", data->map.line_count);	
	printf("%s\n", data->map.map_path);	
}

void mlx_test()
{
	void	*mlx;
	mlx_texture_t*	dark_cat = mlx_load_png("img/dark_cat.png");
	mlx_texture_t*	normal_cat = mlx_load_png("img/normal_cat.png");

	mlx = mlx_init(1600, 900, "aaaaaaa", false);
	mlx_image_t*	normal_cat_image = mlx_texture_to_image(mlx, normal_cat);
	mlx_image_t*	dark_cat_image = mlx_texture_to_image(mlx, dark_cat);
	mlx_resize_image(normal_cat_image, 128, 128);
	mlx_resize_image(dark_cat_image, 128, 128);
	for (int i = 0; i <= 900 / 128; i++)
	{
		for (int j = 0; j <= 1600 / 128; j++)
		{
			//printf("x : %d, y : %d\n", i *)
			if (!(j % 2))
				mlx_image_to_window(mlx, normal_cat_image, j * 128, i * 128);
			else
				mlx_image_to_window(mlx, dark_cat_image, j * 128, i * 128);
		}
	}
	mlx_set_icon(mlx, normal_cat);
	mlx_image_to_window(mlx, normal_cat_image, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

int	main(int argc, char **argv)
{
	t_data	data;

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
