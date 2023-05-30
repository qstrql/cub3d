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
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_pixels(t_ray *ray, mlx_image_t *window, mlx_image_t *img)
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

	(void)img;
	while (i < PIXEL_SIZE)
	{
		j = 0;
		while (j < WIN_HEIGHT)
		{
			if (j < ray->line_offset)
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, 0xB3FFFEFF);
			else if (j >= draw_start && j <= draw_end)
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, ray->cast_color);
			else
				mlx_put_pixel(window,
					(ray->ray_num * PIXEL_SIZE) + i, j, 0x053604FF);
			j++;
		}
		i++;
	}
}

void	get_tile_color(t_ray *ray, t_mapinfo *map)
{
	if (map->map[ray->map_y][ray->map_x] == '1')
		ray->cast_color = 0xFF0000FF;
	else if (map->map[ray->map_y][ray->map_x] == '2')
		ray->cast_color = 0x00FF00FF;
}

void	draw_rays(t_ray *ray, t_player *player, mlx_image_t *window, mlx_image_t *img)
{
	ray->cor_angle = player->angle - ray->ray_angle;
	if (ray->cor_angle < 0)
		ray->cor_angle += 2 * PI;
	if (ray->cor_angle > 2 * PI)
		ray->ray_angle = -2 * PI;
	ray->dist_real = ray->dist_real * cos(ray->cor_angle);
	ray->line_height = (int)(WIN_HEIGHT * 64 / ray->dist_real);
	if (ray->line_height > WIN_HEIGHT)
		ray->line_height = WIN_HEIGHT;
	ray->line_offset = (WIN_HEIGHT / 2) - (ray->line_height / 2);
	draw_pixels(ray, window, img);
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
	mlx_texture_t *cat = mlx_load_png("img/normal_cat.png");
	mlx_image_t		*cat_img = mlx_texture_to_image(mlx, cat);
	mlx_resize_image(cat_img, 32, 32);
	/*for (int x = 0; cat_img->pixels[x]; x++)
	{
		printf("%d : %d\n", x, cat_img->pixels[x]);
	}*/
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
		//get_tile_color(&ray, map);
		draw_rays(&ray, player, window, cat_img);
	}
	mlx_image_to_window(mlx, window, 640, 0);
}