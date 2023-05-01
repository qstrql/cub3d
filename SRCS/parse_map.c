/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:25:39 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 19:54:03 by mjouot           ###   ########.fr       */
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

void remove_empty_lines(char **raw_file)
{
	
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
	remove_empty_lines(raw_file);
	return (raw_file);
}

void parse_map(char *file)
{
	int	i;
	int	line_count;
	t_mapdata mapdata;

	i = 0;
	line_count = get_line_count(file);
	if (line_count < 9)
		exit_msg("Invalid map file");
	mapdata.raw_file = get_raw_file_data(file, line_count);
}

