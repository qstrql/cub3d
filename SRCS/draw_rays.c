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

void	draw_pixels(t_ray *ray, mlx_image_t *window, t_rc_texture *texture, int draw_start, int draw_end, int num)
{
	int	j;
	(void)ray;
	(void)texture;
	//printf("start : %d, end : %d\n", draw_start, draw_end);
	j = 0;
	while (j < WIN_HEIGHT)
	{
		if (j < draw_start)
			mlx_put_pixel(window,
				num, j, 0xb0ad84ff);
		else if (j >= draw_start && j <= draw_end)
		{
			//printf("drawing x : %f, y : %f\n", tx, ty);
			mlx_put_pixel(window,
				num, j, 0xFF0000FF);
		}
		else
			mlx_put_pixel(window,
				num, j, 0xa19d68ff);
		j++;
	}
}

void	cast_rays_3d(mlx_t *mlx, t_player *player, t_mapinfo *map)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
    double	sideDistY;
	double	perpWallDist;
	int		mapX = (int)player->x;
	int		mapY = (int)player->y;
	int		stepX;
	int		stepY;
	int		hit = 0;
	int		side;
	int		screen_line = 0;

	static mlx_image_t	*window = NULL;
	if (window != NULL)
		mlx_delete_image(mlx, window);
	window = mlx_new_image(mlx, WIN_WIDTH * 2, WIN_HEIGHT * 2);

	while (screen_line < WIN_WIDTH)
	{
		cameraX = 2 * screen_line / (double)WIN_WIDTH - 1;
		rayDirX = player->dir_x + player->plane_x * cameraX;
		rayDirY = player->dir_y + player->plane_y * cameraX;
		mapX = (int)player->x;
		mapY = (int)player->y;
		hit = 0;
		if (rayDirX != 0)
			deltaDistX = fabs(1 / rayDirX);
		else
			deltaDistX = 1e30;
		if (rayDirY != 0)
			deltaDistY = fabs(1 / rayDirY);
		else
			deltaDistY = 1e30;
		//printf("cameraX : %f, rayDirX : %f, rayDirY : %f, deltaDistX : %f, deltaDistY : %f\n", cameraX, rayDirX, rayDirY, deltaDistX, deltaDistY);
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
        		mapY += stepY;
        		side = 1;
			}
			if (map->map[mapX][mapY] != '0')
			{
				//printf("hit [%d,%d]\n", mapX, mapY);
				hit = 1;
			}
		}
		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;
		/*if (drawStart > drawEnd)
		{
			int tmp;
			tmp = drawEnd;
			drawEnd = drawStart;
			drawStart = tmp;
		}*/
		//printf("draw start : %d\n", drawStart);
	//	printf("draw end : %d\n", drawEnd);
		draw_pixels(NULL, window, NULL, drawStart, drawEnd, screen_line);
		screen_line++;
	}
	mlx_image_to_window(mlx, window, 0, 0);
}