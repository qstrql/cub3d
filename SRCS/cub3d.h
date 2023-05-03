/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 22:07:44 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/INCLUDES/libft.h"

/* ************************************************************************** */
/*                                  DEFINE & ENUMS                            */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

enum e_rgb
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};

/* ************************************************************************** */
/*                                  STRUCTURES                                */
/* ************************************************************************** */

typedef struct s_mapdata
{
	char **raw_file;
	char *no_texture_path;
	char *so_texture_path;
	char *we_texture_path;
	char *ea_texture_path;
	int floor[3];
	int ceiling[3];
}				t_mapdata;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_mapdata	mapdata;
	char		**raw_file;
}	t_data;

/* ************************************************************************** */
/*                                  FUNCTIONS                                 */
/* ************************************************************************** */

//init_structs.c
void	init_mapdata_struct(t_mapdata *mapdata);
void	init_data_struct(t_data *data);

//exit_program.c
void	close_window(t_data *data);
void	exit_program(t_data *data, int exit_code);

//free_data_struct.c
void	free_mapdata_struct(t_mapdata *mapdata);
void	free_data_struct(t_data *data);

//gnl.c
char	*get_next_line(int fd);

//parse_map.c
void parse_map(t_data *data, char *file);

//parse_arg.c
bool file_exist(char *argv);
bool file_is_a_directory(char *file);
bool check_map_extension(char *argv);
void parse_arg(t_data *data, char *argv);

//utils.c
void	exit_msg(t_data *data, char *str);

#endif
