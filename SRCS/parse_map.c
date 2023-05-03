/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:25:39 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:11:31 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

bool check_line_lenght(char **raw_file)
{
	int	i;
	char **tmp;

	i = 0;
	while (raw_file[i])
	{
		if (str_is_space_only(raw_file[i]) == true)
			i++;
		tmp = ft_split(raw_file[i], ' ');
		if (tmp[2])
		{
			free_split_array(&tmp);
			return (false);
		}
		free_split_array(&tmp);
		i++;
	}
	return (true);
}

int	texture_coord(char *coord)
{
	if (ft_strncmp(coord, "SO", 3))
		return (1);
	if (ft_strncmp(coord, "NO", 3))
		return (1);
	if (ft_strncmp(coord, "WE", 3))
		return (1);
	if (ft_strncmp(coord, "EA", 3))
		return (1);
	return (0);
}	

bool check_texture_path(char **raw_file)
{
	int	i;
	char **tmp;

	i = 0;
	while (raw_file[i]) 
	{
		if (str_is_space_only(raw_file[i]) == true)
			i++;
		tmp = ft_split(raw_file[i], ' ');
		if (!texture_coord(tmp[0]) &&
				(file_exist(tmp[1]) && !file_is_a_directory(tmp[1])))
		{
			free_split_array(&tmp);	
			return (false);
		}
		free_split_array(&tmp);	
		i++;
	}
	return (true);
}

void parse_raw_file_data(t_data *data)
{
	if (check_line_lenght(data->raw_file) == false)
		exit_msg(data, "Invalid map file");
	if (check_texture_path(data->raw_file) == false)
		exit_msg(data, "Invalid map file");
	
}

void parse_map(t_data *data, char *file)
{
	int	i;

	i = 0;
	if (get_line_count(file) < 9)
		exit_msg(data, "Invalid map file");
	data->raw_file = get_raw_file_data(file);
	parse_raw_file_data(data);
}
