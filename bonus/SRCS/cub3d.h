/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:47 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:55:28 by mjouot           ###   ########.fr       */
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
# include "../../libft/INCLUDES/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"

/*-----------------DEFINES & ENUMS--------------------------------------------*/

# define BUFFER_SIZE 1

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
# define WRONG_TEXTURE_PATH "Wrong texture path"
# define MINIMAP_FILES_MISSING "Minimap textures are missing"
# define BAD_MAP "Map is invalid"
# define BAD_CHARACTERS "Map contains invalid characters"
# define PLAYER_MISSING "Player is missing from the map"
# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define TEXTURE_WIDTH 256
# define TEXTURE_HEIGHT 256
# define SENSITIVITY 5

enum e_rgb
{
	RED = 0,
	GREEN = 1,
	BLUE = 2,
};

/*-----------------STRUCTURES-------------------------------------------------*/

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgb;

typedef struct s_rc_texture
{
	t_rgb	*pixels;
	int		width;
	int		height;
}	t_rc_texture;

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
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	t_rc_texture	*textures[6];
	t_rc_texture	*door_anim[10];
	t_rgb			floor;
	t_rgb			ceiling;
}				t_config;

typedef struct s_minimap
{
	int					cell_size;
	mlx_texture_t		**textures;
	mlx_image_t			**images;
}	t_minimap;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
	int			map_pos_x;
	int			map_pos_y;
	t_minimap	minimap;
}	t_player;

typedef struct s_game
{
	mlx_t			*mlx;
	t_mapinfo		*mapinfo;
	t_player		*player;
	t_config		config;
	char			**raw_file;
}	t_game;

typedef struct s_ray
{
	int		num;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	double	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	char	*hit;
	int		side;
}	t_ray;

/*-----------------FUNCTIONS--------------------------------------------------*/

//debug.c
void			ft_printf_strs(char **strs);
void			debugprint(t_game *data);
void			display_map(t_game *game);

//init_structs.c
void			init_mapinfo_struct(t_mapinfo *map);
void			init_config_struct(t_config *config);
void			init_data_struct(t_game *data);

//exit_program.c
void			exit_game(t_game *data, int exit_code);

//free_data_struct.c
void			free_mapinfo_struct(t_mapinfo *map);
void			free_config_struct(t_config *config);
int				free_data_struct(t_game *data, int exit_code);

//free_textures.c
void			free_game_textures(t_game *game);

//gnl.c
char			*get_next_line(int fd);

//get_file_content.c
void			get_file_content(t_game *data, char *file_path);
char			**get_raw_file_data(char *file);
int				get_line_count(char *file);

//parse_file.c
int				parse_file(t_game *data, char *argv);
int				check_file_content(t_game *data);

//check_file_content_utils.c
int				get_content(t_game *data, int i);
int				get_coord_path(t_config *config, char **line);
int				get_texture_rgb(t_config *config, char **line);
void			get_map(t_game *data, int i);
void			remove_map_nl(t_mapinfo *map);

//get_rgb.c
int				get_rbg(t_config *config, char **line);
int				fill_ceiling_rgb(t_config *config, char **tmp);
int				fill_floor_rgb(t_config *config, char **tmp);

//check_textures.c
int				verify_minimap_textures(void);
int				verify_texture_path(t_game *data);

//check_map.c
int				verify_map_validity(t_game *data);
int				verify_map_down(t_game *data);
int				verify_map_up(t_game *data);
int				verify_map_right(t_game *data);
int				verify_map_left(t_game *data);

//check_map_utils.c
int				verify_player_present(t_game *data);
int				verify_map_characters(t_game *data);

//init_utils.c
void			init_player(t_player *player, mlx_t *mlx, t_mapinfo *map);
void			init_minimap(t_player *player, mlx_t *mlx, t_mapinfo *map);
int				init_minimap_textures(mlx_t *mlx, t_minimap *minimap);
void			set_player_init_pos(t_player *player, t_mapinfo *map);
void			set_player_rotation(t_player *player, char rotation);

//input_hook_setup.c
void			secondary_input_hook(t_game *game, bool *interact, char *rot);
void			input_hook(void *param);

//player_utils.c
void			player_loop(t_game *game, char direction,
					char rotation, bool interact);
void			player_interact(t_game *game);
void			strafe_player(t_player *player,
					t_mapinfo *mapinfo, char direction);
void			move_player(t_player *player,
					t_mapinfo *mapinfo, char direction);
void			rotate_player(t_player *player, char rotation);

//display_to_screen.c
int				reload_map_assets(mlx_t *mlx, t_minimap *minimap);
void			put_tiles_to_screen(t_game *game, int i, int j, int middle);
void			display_map(t_game *game);

//check_utils.c
int				check_for_correct_rgb(char *rgb);
int				check_for_correct_coord(char *coord);
bool			check_if_struct_filled(t_config *config);

//parse_arg.c
bool			file_exist(char *argv);
bool			file_is_a_directory(char *file);
bool			check_map_extension(char *argv);
int				parse_arg(char *argv);

//utils.c
int				str_array_len(char **strs);
int				error_msg(char *str, int exit_code);
void			exit_msg(t_game *data, char *str);

//cast_rays.c
void			initial_ray_calculations(t_ray *ray, t_player *player);
void			dda_init_calculations(t_ray *ray, t_player *player);
void			dda_calculations(t_ray *ray, t_mapinfo *map);

//draw_rays.c
void			draw(mlx_image_t *window,
					t_rc_texture *texture, int line[], t_config *config);
void			cast_rays_3d(mlx_t *mlx, t_player *player,
					t_mapinfo *map, t_config *config);
void			draw_rays(mlx_image_t *window, t_ray *ray,
					t_player *player, t_config *config);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);

//rc_texture_utils.c
void			free_rc_texture(t_rc_texture *texture);
t_rc_texture	*init_rc_texture(char *path, mlx_t *mlx);
t_rgb			get_rgb_value(t_rc_texture texture, int x, int y);
int32_t			color_int32(t_rgb rgb);
#endif
