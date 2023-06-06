/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:35:46 by lbertaux          #+#    #+#             */
/*   Updated: 2023/05/27 16:35:49 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_pixels(mlx_image_t *window,
			t_rc_texture *texture, int line[], int num)
{
	//int 	i;
	int		j;
	double	step;

	step = 1.0 * TEXTURE_HEIGHT / line[2];
	double	texture_pos = (line[0] - WIN_HEIGHT / 2 + line[2] / 2) * step;
	(void)texture;
	j = line[0];
	while (j >= line[0] && j < line[1])
	{
		int	texture_y = (int)texture_pos & (TEXTURE_HEIGHT - 1);
		texture_pos += step;
		uint32_t color = color_int32(get_rgb_value(*texture, line[3], texture_y));
		mlx_put_pixel(window, num, j, color);
		j++;
	}
}

void	draw_rays(mlx_image_t *window, t_ray *ray, t_player *player, t_rc_texture *textures[])
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		line[4];
	double	wall_x;

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
	//wall_x calculates where exactly the wall was hit from the player
	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	
	//texture_x gets coords of the texture
	int texture_x = (int)(wall_x * (double)TEXTURE_WIDTH);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		texture_x = TEXTURE_WIDTH - texture_x - 1;
	line[3] = texture_x;
	draw_pixels(window, textures[2], line, ray->num);
}

void	cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map, t_rc_texture *textures[])
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
		draw_rays(window, &ray, player, textures);
		ray.num++;
	}
	mlx_image_to_window(mlx, window, 0, 0);
}
