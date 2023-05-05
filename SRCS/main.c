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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(USAGE, EXIT_FAILURE));
	init_data_struct(&data);
	if (parse_file(&data, argv[1]) != VALID_FILE)
		return (INVALID_FILE);
	debugprint(&data);
	free_data_struct(&data, EXIT_SUCCESS);
}
