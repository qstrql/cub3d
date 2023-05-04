/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/04 15:12:58 by mjouot           ###   ########.fr       */
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

/*-----------------DEFINES & ENUMS--------------------------------------------*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define VALID_FILE 1
# define INVALID_FILE 0
# define FAIL 0

# define USAGE "Wrong number of arguments, use ./cub3D <path/map_name.cub>"
# define FILE_IS_DIR "This file is a directory"
# define WRONG_FILE_EXTENSION "The file's extension is wrong"
# define FILE_WITHOUT_EXTENSION "The file provided does not have an extension"
# define FILE_DOESNT_EXIST "The provided file does not exist"

enum e_rgb
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};

/*-----------------STRUCTURES-------------------------------------------------*/

typedef struct s_mapinfo
{
	int			fd;
	int			line_count;
	int			height;
	int			width;
	int			eof;
	char		*map_path;
	char		**map;
}	t_mapinfo;

typedef struct s_textureinfo
{
	char	*no_texture_path;
	char 	*so_texture_path;
	char 	*we_texture_path;
	char 	*ea_texture_path;
	int 	floor[3];
	int 	ceiling[3];
}				t_textureinfo;

typedef struct s_data
{
	void			*mlx;
	void			*window;
	t_textureinfo	texture;
	t_mapinfo		map;
	char			**raw_file;
}	t_data;

/*-----------------FUNCTIONS--------------------------------------------------*/

//init_structs.c
void	init_mapinfo_struct(t_mapinfo *map);
void	init_textureinfo_struct(t_textureinfo *texture);
void	init_data_struct(t_data *data);

//exit_program.c
void	close_window(t_data *data);
void	exit_program(t_data *data, int exit_code);

//free_data_struct.c
void	free_mapinfo_struct(t_mapinfo *map);
void	free_textureinfo_struct(t_textureinfo *texture);
int		free_data_struct(t_data *data, int exit_code);

//gnl.c
char	*get_next_line(int fd);

//parse_file.c
int	get_line_count(char *file);
char **get_raw_file_data(char *file);
void get_file_content(t_data *data, char *file);

//parse_arg.c
bool file_exist(char *argv);
bool file_is_a_directory(char *file);
bool check_map_extension(char *argv);
int	parse_arg(char *argv);

//utils.c
int		error_msg(char *str, int exit_code);
void	exit_msg(t_data *data, char *str);

#endif
