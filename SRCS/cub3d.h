/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 19:37:20 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/INCLUDES/libft.h"

typedef struct s_mapdata
{
	char **raw_file;
	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	int floor[3];
	int ceiling[3];
	char **map;
}				t_mapdata;

//gnl.c
char	*get_next_line(int fd);

//parse_map.c
void parse_map(char *file);

//parse_arg.c
bool file_exist(char *argv);
bool check_map_extension(char *argv);
void parse_arg(char *argv);

//utils.c
void	better_free(void *ptr);
int	exit_msg(char *str);

#endif
