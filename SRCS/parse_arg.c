/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:39:07 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/02 11:54:53 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"
#include <stdbool.h>

bool file_exist(char *file)
{
	int	tmp_fd;

	tmp_fd = open(file, O_RDONLY);
	if (tmp_fd == -1 && errno == ENOENT)
		return (false);
	else
	{
		close(tmp_fd);
		return (true);
	}
}

bool check_map_extension(char *argv)
{
	size_t len;
	len = ft_strlen(argv);
    if (len >= 4 && ft_strncmp(argv + len - 4, ".cub", 5) == 0)
        return (true);
    else
        return (false);
}

bool file_is_a_directory(char *file)
{
	int	tmp_fd;

	tmp_fd = open(file, O_DIRECTORY);
	if (tmp_fd >= 0)
	{
		close(tmp_fd);
		return (true);
	}
	return (false);
}

void parse_arg(char *argv)
{
	if (file_is_a_directory(argv) == true)
		exit_msg("This file is a directory");
	if (ft_strchr(argv, '.'))
	{
		if (check_map_extension(argv) == false)
			exit_msg("The file extension is wrong, it must end in .cub");
	}
	else
		exit_msg("The file provided does not have an extension");
	if (file_exist(argv) == false)
		exit_msg("The file provided does not exist");
}
