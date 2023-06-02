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

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	//printf("r : %d, g : %d, b : %d, a : %d\n", r, g, b, a);
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_pixels(t_ray *ray, mlx_image_t *window, t_rc_texture *texture)
{
	int	i;
	int	j;
	int	draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int	draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end < 0)
		draw_end = 0;
	i = 0;

	float	tx;
	float	ty = ray->texture_step * ray->texture_offset;
	//printf("step : %f, offset : %f\n", ray->texture_step, ray->texture_offset);
	if (!ray->vertical)
		tx = (int)(ray->ray_x / (64 / texture->width)) % texture->width;
	else
		tx = (int)(ray->ray_y / (64 / texture->width)) % texture->width;

	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			if (j < ray->line_offset)
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, 0xB3FFFEFF);
			else if (j >= draw_start && j <= draw_end)
			{
				//printf("drawing x : %f, y : %f\n", tx, ty);
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, color_int32(texture->pixels[(int)ty * texture->width + (int)tx]));
				ty += ray->texture_step;
			}
			else
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, 0x053604FF);
			j++;
		}
		i++;
		ty = ray->texture_step * ray->texture_offset;
	}
	//mlx_put_pixel(window,
	//				(ray->ray_num * PIXEL_SIZE) + i, j, ft_pixel(texture->pixels[pixel], texture->pixels[pixel + 1], texture->pixels[pixel + 2], texture->pixels[pixel + 3]));
}

void	draw_rays(t_ray *ray, t_player *player, mlx_image_t *window, t_rc_texture *texture)
{
	ray->cor_angle = player->angle - ray->ray_angle;
	if (ray->cor_angle < 0)
		ray->cor_angle += 2 * PI;
	if (ray->cor_angle > 2 * PI)
		ray->ray_angle = -2 * PI;
	ray->dist_real = ray->dist_real * cos(ray->cor_angle);
	ray->line_height = (int)(WIN_HEIGHT * 64 / ray->dist_real);
	ray->texture_step = texture->height / (float)ray->line_height;
	ray->texture_offset = 0;
	if (ray->line_height > WIN_HEIGHT)
	{
		ray->texture_offset = (ray->line_height - WIN_HEIGHT) / 2;
		ray->line_height = WIN_HEIGHT;
	}
	ray->line_offset = (WIN_HEIGHT / 2) - (ray->line_height / 2);
	draw_pixels(ray, window, texture);
	ray->ray_num++;
	ray->ray_angle += RAD1;
	if (ray->ray_angle < 0)
		ray->ray_angle += 2 * PI;
	if (ray->ray_angle > 2 * PI)
		ray->ray_angle = -2 * PI;
}

void	cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map)
{
	static mlx_image_t	*window = NULL;
	t_rc_texture *cat_texture;
	t_ray				ray;

	if (window != NULL)
		mlx_delete_image(mlx, window);
	cat_texture = init_rc_texture("img/wallpaper.png", mlx);
	window = mlx_new_image(mlx, WIN_WIDTH * 2, WIN_HEIGHT * 2);
	ray.hit_x_hor = player->x;
	ray.hit_y_hor = player->y;
	ray.ray_angle = 0;
	ray.ray_angle = set_angle(ray.ray_angle, player->angle - (RAD1 * 30));
	ray.ray_num = 0;
	while (ray.ray_num < RAYS)
	{
		initial_horizontal_math(&ray, player);
		ray_collision_check_horizontal(&ray, player, map);
		initial_vertical_math(&ray, player);
		ray_collision_check_vertical(&ray, player, map);
		check_distance(&ray);
		draw_rays(&ray, player, window, cat_texture);
	}
	mlx_image_to_window(mlx, window, 640, 0);
}