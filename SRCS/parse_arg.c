/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 16:39:07 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 23:04:05 by mjouot           ###   ########.fr       */
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

int	parse_arg(char *argv)
{
	if (file_exist(argv) == false)
		return (error_msg(FILE_DOESNT_EXIST, INVALID_FILE));
	if (ft_strchr(argv, '.'))
	{
		if (check_map_extension(argv) == false)
			return (error_msg(WRONG_FILE_EXTENSION, INVALID_FILE));
		if (file_is_a_directory(argv) == true)
			return (error_msg(FILE_IS_DIR, INVALID_FILE));
	}
	else
		return (error_msg(FILE_WITHOUT_EXTENSION, INVALID_FILE));
	return (VALID_FILE);
}
