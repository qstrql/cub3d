/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:35:46 by lbertaux          #+#    #+#             */
/*   Updated: 2023/06/06 11:36:35 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw(mlx_image_t *window,
			t_rc_texture *texture, int line[], t_config *config)
{
	int			i;
	double		step;
	uint32_t	color;
	int			texture_y;
	double		texture_pos;

	step = 1.0 * TEXTURE_HEIGHT / line[2];
	texture_pos = (line[0] - WIN_HEIGHT / 2 + line[2] / 2) * step;
	i = 0;
	while (i < WIN_HEIGHT)
	{
		if (i < line[0])
			color = color_int32(config->floor);
		if (i >= line[0] && i < line[1])
		{
			texture_y = (int)texture_pos & (TEXTURE_HEIGHT - 1);
			texture_pos += step;
			color = color_int32(get_rgb_value(*texture, line[3], texture_y));
		}
		else if (i >= line[1])
			color = color_int32(config->ceiling);
		mlx_put_pixel(window, line[4], i, color);
		i++;
	}
}

int	*get_line_values(t_ray *ray)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		*line;

	line = ft_calloc(6, sizeof(int));
	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	line[0] = draw_start;
	line[1] = draw_end;
	line[2] = line_height;
	line[4] = ray->num;
	return (line);
}

void	draw_rays(mlx_image_t *window, t_ray *ray,
			t_player *player, t_config *config)
{
	int		*line;
	double	wall_x;

	line = get_line_values(ray);
	wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	wall_x -= floor(wall_x);
	line[3] = (int)(wall_x * (double)TEXTURE_WIDTH);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		line[3] = TEXTURE_WIDTH - line[3] - 1;
	if (ray->side == 0 && ray->ray_dir_x <= 0)
		draw(window, config->textures[0], line, config);
	else if (ray->side == 0)
		draw(window, config->textures[2], line, config);
	else if (ray->side == 1 && ray->ray_dir_y >= 0)
		draw(window, config->textures[1], line, config);
	else
		draw(window, config->textures[3], line, config);
	free(line);
}

void	cast_rays_3d(mlx_t *mlx, t_player *player,
			t_mapinfo *map, t_config *config)
{
	t_ray				ray;
	static mlx_image_t	*window = NULL;

	if (window != NULL)
		mlx_delete_image(mlx, window);
	window = mlx_new_image(mlx, WIN_WIDTH * 2, WIN_HEIGHT * 2);
	ray.num = 0;
	while (ray.num < WIN_WIDTH)
	{
		initial_ray_calculations(&ray, player);
		dda_init_calculations(&ray, player);
		dda_calculations(&ray, map);
		draw_rays(window, &ray, player, config);
		ray.num++;
	}
	mlx_image_to_window(mlx, window, 0, 0);
	window->instances[0].z = -1;
}
