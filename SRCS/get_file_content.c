/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_content.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:25:39 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/06 11:48:24 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int	get_line_count(char *file)
{
	int	tmp_fd;
	int	line_count;
	char *line;

	line_count = 0;
	tmp_fd = open(file, O_RDONLY);
	line = get_next_line(tmp_fd);
	while (line != NULL)
	{
		line_count++;
		free(line);
		line = get_next_line(tmp_fd);
	}
	close(tmp_fd);
	return (line_count);
}

char **get_raw_file_data(char *file)
{
	int	i;
	int	tmp_fd;
	char *line;
	int	line_count;
	char **raw_file;

	i = 0;
	tmp_fd = open(file, O_RDONLY);
	line_count = get_line_count(file);
	raw_file = ft_calloc(line_count + 1, sizeof(char *));
	line = get_next_line(tmp_fd);
	while (line != NULL)
	{
		raw_file[i] = ft_strdup(line);
		free(line);
		line = get_next_line(tmp_fd);
		i++;
	}
	close(tmp_fd);
	return (raw_file);
}

void get_file_content(t_game *data, char *file_path)
{
	int	i;
	int	line_count;

	i = 0;
	line_count = get_line_count(file_path);
	data->mapinfo->line_count = line_count;
	data->mapinfo->map_path = ft_strdup(file_path); 
	data->raw_file = get_raw_file_data(file_path);
}
