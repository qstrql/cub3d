/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 17:27:02 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <asm-generic/errno-base.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/INCLUDES/libft.h"

typedef struct s_mapfile
{
	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	int floor[3];
	int ceiling[3];
	char **map;
}				t_mapfile;

//parse_arg.c
void parse_map(char *file);

//parse_arg.c
bool file_exist(char *argv);
bool check_map_extension(char *argv);
void parse_arg(char *argv);

//utils.c
int	exit_msg(char *str);

#endif
