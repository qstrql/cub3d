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

void	draw_pixels(t_ray *ray, mlx_image_t *window)
{
	int	i;
	int	j;

	i = 0;
	while (i < PIXEL_SIZE)
	{
		j = ray->line_offset;
		while (j < ray->line_height + ray->line_offset)
		{
			mlx_put_pixel(window,
				(ray->ray_num * PIXEL_SIZE) + i, j, ray->cast_color);
			j++;
		}
		i++;
	}
}

void	draw_rays(t_ray *ray, t_player *player, mlx_image_t *window)
{
	ray->cor_angle = player->angle - ray->ray_angle;
	if (ray->cor_angle < 0)
		ray->cor_angle += 2 * PI;
	if (ray->cor_angle > 2 * PI)
		ray->ray_angle = -2 * PI;
	ray->dist_real = ray->dist_real * cos(ray->cor_angle);
	ray->line_height = (64 * WIN_HEIGHT) / ray->dist_real;
	if (ray->line_height > WIN_HEIGHT)
		ray->line_height = WIN_HEIGHT;
	ray->line_offset = (WIN_HEIGHT / 2) - (ray->line_height / 2);
	draw_pixels(ray, window);
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
	t_ray				ray;

	if (window != NULL)
		mlx_delete_image(mlx, window);
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
		draw_rays(&ray, player, window);
	}
	mlx_image_to_window(mlx, window, 0, 0);
}