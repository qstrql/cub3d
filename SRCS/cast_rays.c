/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <lbertaux@student.42angouleme.fr>     +#+  +:+       +#+    */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 21:53:42 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/27 16:28:01 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	ray_collision_check_horizontal(t_ray *ray,
			t_player *player, t_mapinfo *map)
{
	while (ray->dof < 8)
	{
		ray->map_x = (int)(ray->ray_x) >> 6;
		ray->map_y = (int)(ray->ray_y) >> 6;
		if (ray->map_x >= 0 && ray->map_y >= 0)
		{
			if (ray->map_x < map->width && ray->map_y < map->height
				&& map->map[ray->map_y][ray->map_x] != '0')
			{
				ray->hit_x_hor = ray->ray_x;
				ray->hit_y_hor = ray->ray_y;
				ray->dist_h = dist(player->x, player->y,
						ray->hit_x_hor, ray->hit_y_hor);
				ray->dof = 8;
				break ;
			}
		}
		ray->ray_x += ray->xo;
		ray->ray_y += ray->yo;
		ray->dof += 1;
	}
	if (ray->ray_x > (float)INT_MAX - 1 || ray->ray_x < INT_MIN)
		ray->ray_x = player->x;
	if (ray->ray_y > (float)INT_MAX - 1 || ray->ray_y < INT_MIN)
		ray->ray_y = player->y;
}

void	initial_horizontal_math(t_ray *ray, t_player *player)
{
	ray->dof = 0;
	ray->dist_h = 10000000;
	ray->dist_v = 10000000;
	ray->aTan = -1 / tan(ray->ray_angle);
	if (ray->ray_angle > PI)
	{
		ray->ray_y = (((int)player->y / 64) * 64) - 0.0001;
		ray->ray_x = (player->y - ray->ray_y) * ray->aTan + player->x;
		ray->yo = -64;
		ray->xo = -ray->yo * ray->aTan;
	}
	else if (ray->ray_angle < PI)
	{
		ray->ray_y = (((int)player->y / 64) * 64) + 64;
		ray->ray_x = (player->y - ray->ray_y) * ray->aTan + player->x;
		ray->yo = 64;
		ray->xo = -ray->yo * ray->aTan;
	}
	if (ray->ray_angle == 0 || ray->ray_angle == PI * 2)
	{
		ray->ray_x = player->x;
		ray->ray_y = player->y;
		ray->dof = 8;
	}
}

void	ray_collision_check_vertical(t_ray *ray,
			t_player *player, t_mapinfo *map)
{
	while (ray->dof < 8)
	{
		ray->map_x = (int)(ray->ray_x) >> 6;
		ray->map_y = (int)(ray->ray_y) >> 6;
		if (ray->map_x >= 0 && ray->map_y >= 0)
		{
			if (ray->map_x < map->width && ray->map_y < map->height
				&& map->map[ray->map_y][ray->map_x] != '0')
			{
				ray->hit_x_ver = ray->ray_x;
				ray->hit_y_ver = ray->ray_y;
				ray->dist_v = dist(player->x, player->y,
						ray->hit_x_ver, ray->hit_y_ver);
				ray->dof = 8;
				break ;
			}
		}
		ray->ray_x += ray->xo;
		ray->ray_y += ray->yo;
		ray->dof += 1;
	}
	if (ray->ray_x > (float)INT_MAX - 1 || ray->ray_x < INT_MIN)
		ray->ray_x = player->x;
	if (ray->ray_y > (float)INT_MAX - 1 || ray->ray_y < INT_MIN)
		ray->ray_y = player->y;
}

void	initial_vertical_math(t_ray *ray, t_player *player)
{
	ray->dof = 0;
	ray->nTan = -tan(ray->ray_angle);
	ray->hit_x_ver = player->x;
	ray->hit_y_ver = player->y;
	if (ray->ray_angle > PI2 && ray->ray_angle < PI3)
	{
		ray->ray_x = (((int)player->x / 64) * 64) - 0.0001;
		ray->ray_y = (player->x - ray->ray_x) * ray->nTan + player->y;
		ray->xo = -64;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (ray->ray_angle < PI2 || ray->ray_angle > PI3)
	{
		ray->ray_x = (((int)player->x / 64) * 64) + 64;
		ray->ray_y = (player->x - ray->ray_x) * ray->nTan + player->y;
		ray->xo = 64;
		ray->yo = -ray->xo * ray->nTan;
	}
	if (ray->ray_angle == 0 || ray->ray_angle == PI * 2)
	{
		ray->ray_x = player->x;
		ray->ray_y = player->y;
		ray->dof = 8;
	}
}
