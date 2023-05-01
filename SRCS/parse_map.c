/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:25:39 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 18:21:45 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

static bool check_map_content(int fd)
{
	char *line;

	line = get_next_line(fd);
	
	return (true);
}

void parse_map(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (check_map_content(fd) == false)
	{
		close(fd);
		exit_msg("Invalid map file content");
	}
	close(fd);
}

