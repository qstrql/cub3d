/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:25:39 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/02 00:08:56 by mjouot           ###   ########.fr       */
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

void remove_empty_lines(char **raw_file, int line_count)
{
	int	i;
	int	j;

	i = 0;
	while (i < line_count)
	{
		if (str_is_space_only(raw_file[i]) == true)
		{
			j = i;
			free(raw_file[i]);
			while (j < line_count - 1)
			{
				raw_file[j] = raw_file[j + 1];
				j++;
			}
			line_count--;
		}
		else
			i++;
	}
}

char **get_raw_file_data(char *file, int line_count)
{
	int	i;
	int	tmp_fd;
	char *line;
	char **raw_file;

	i = 0;
	tmp_fd = open(file, O_RDONLY);
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
	remove_empty_lines(raw_file, line_count);
	return (raw_file);
}
bool check_line_lenght(char **raw_file)
{
	int	i;
	char **tmp;

	i = 0;
	while (i < 6)
	{
		tmp = ft_split(raw_file[i], ' ');
		if (tmp[2])
		{
			free_split_array(&tmp);
			free_split_array(&raw_file);
			return (false);
		}
		free_split_array(&tmp);
		i++;
	}
	return (true);
}
void parse_raw_file_data(char **raw_file)
{
	if (check_line_lenght(raw_file) == false)
		exit_msg("Invalid map file");
}

void parse_map(char *file)
{
	int	i;
	int	line_count;
	char **raw_file;

	i = 0;
	line_count = get_line_count(file);
	if (line_count < 9)
		exit_msg("Invalid map file");
	raw_file = get_raw_file_data(file, line_count);
	parse_raw_file_data(raw_file);
}
