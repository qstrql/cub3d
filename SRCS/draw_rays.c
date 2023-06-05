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
	int	j;

	(void)texture;
	j = 0;
	while (j < WIN_HEIGHT)
	{
		if (j < line[0])
			mlx_put_pixel(window, num, j, 0xb0ad84ff);
		else if (j >= line[0] && j <= line[1])
		{
			mlx_put_pixel(window, num, j, 0xFF0000FF);
		}
		else
			mlx_put_pixel(window, num, j, 0xa19d68ff);
		j++;
	}
}

void	draw_rays(mlx_image_t *window, t_ray *ray)
{
	int	line_height;
	int	draw_start;
	int	draw_end;
	int	line[2];

	line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	line[0] = draw_start;
	line[1] = draw_end;
	draw_pixels(window, NULL, line, ray->num);
}

void	cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map)
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
		draw_rays(window, &ray);
		ray.num++;
	}
	mlx_image_to_window(mlx, window, 0, 0);
}
