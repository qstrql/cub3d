/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/06 00:07:28 by mjouot           ###   ########.fr       */
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
# include <limits.h>
# include "../libft/INCLUDES/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"
/*-----------------DEFINES & ENUMS--------------------------------------------*/

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

# define VALID_FILE 1
# define INVALID_FILE 0
# define FAIL 0
# define SUCCESS 1

# define USAGE "Wrong number of arguments, use ./cub3D <path/map_name.cub>"
# define FILE_IS_DIR "This file is a directory"
# define WRONG_FILE_EXTENSION "The file's extension is wrong"
# define FILE_WITHOUT_EXTENSION "The file provided does not have an extension"
# define FILE_DOESNT_EXIST "The provided file does not exist"
# define WRONG_FILE_CONTENT "File content is wrong or missing"

# define PI 3.141592
# define PI2 PI/2
# define PI3 3*PI/2
# define RAD1 0.0174533

# define RAYS 60
# define PIXEL_SIZE 8
# define WIN_WIDTH PIXEL_SIZE * RAYS + 640
# define WIN_HEIGHT 600

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

typedef struct s_config
{
	char	*no;
	char 	*so;
	char 	*we;
	char 	*ea;
	int 	*floor;
	int 	*ceiling;
}				t_config;

typedef struct s_sprite
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;
}	t_sprite;

typedef struct s_player
{
	t_sprite	sprite;
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		angle;
	int			map_pos_x;
	int			map_pos_y;
}	t_player;

typedef struct s_game
{
	mlx_t		*mlx;
	t_mapinfo	*mapinfo;
	t_player	*player;
	t_config		config;
	char			**raw_file;
}	t_game;

typedef struct s_ray
{
	bool	vertical;
	int		ray_num;
	int		map_x;
	int		map_y;
	int		hor_map_x;
	int		hor_map_y;
	int		ver_map_x;
	int		ver_map_y;
	int		dof;
	float	texture_offset;
	float	texture_step;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	xo;
	float	yo;
	float	dist_h;
	float	dist_v;
	float	hit_x_hor;
	float	hit_y_hor;
	float	hit_x_ver;
	float	hit_y_ver;
	float	dist_real;
	float	aTan;
	float	nTan;
	float	line_height;
	float	line_offset;
	float	cor_angle;
}	t_ray;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgb;

typedef struct	s_rc_texture
{
	t_rgb	*pixels;
	int	width;
	int	height;
}	t_rc_texture;

/*-----------------FUNCTIONS--------------------------------------------------*/

void			debugprint(t_game *data);

//init_structs.c
void			init_mapinfo_struct(t_mapinfo *map);
void			init_config_struct(t_config *config);
void			init_data_struct(t_game *data);

//exit_program.c
void			close_window(t_game *data);
void			exit_program(t_game *data, int exit_code);

//free_data_struct.c
void			free_mapinfo_struct(t_mapinfo *map);
void			free_config_struct(t_config *config);
int				free_data_struct(t_game *data, int exit_code);

//gnl.c
char			*get_next_line(int fd);

//parse_file.c
int				get_line_count(char *file);
char			**get_raw_file_data(char *file);
void			get_file_content(t_game *data, char *file);

//parse_arg.c
bool			file_exist(char *argv);
bool			file_is_a_directory(char *file);
bool			check_map_extension(char *argv);
int				parse_arg(char *argv);

//utils.c
int				error_msg(char *str, int exit_code);
void			exit_msg(t_game *data, char *str);

//cast_rays.c
void			ray_collision_check_horizontal(t_ray *ray,
			t_player *player, t_mapinfo *map);
void			initial_horizontal_math(t_ray *ray, t_player *player);
void			ray_collision_check_vertical(t_ray *ray,
			t_player *player, t_mapinfo *map);
void			initial_vertical_math(t_ray *ray, t_player *player);

//cast_rays_utils.c
float			set_angle(float angle, float wanted_value);
void			check_distance(t_ray *ray);
float			dist(float ax, float ay, float bx, float by);

//draw_rays.c
void    		draw_pixels(t_ray *ray, mlx_image_t *window, t_rc_texture *texture);
void			draw_rays(t_ray *ray, t_player *player, mlx_image_t *window, t_rc_texture *texture);
void			cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//rc_texture_utils.c
t_rgb			*texture_to_rgb_array(mlx_texture_t *texture);
void			free_rc_texture(t_rc_texture *texture);
t_rc_texture	*init_rc_texture(char *path, mlx_t *mlx);
t_rgb			get_rgb_value(t_rc_texture texture, int x, int y);
int32_t			color_int32(t_rgb rgb);
#endif
