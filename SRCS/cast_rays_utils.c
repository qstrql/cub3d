/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:29:45 by lbertaux          #+#    #+#             */
/*   Updated: 2023/05/27 16:29:46 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

float	set_angle(float angle, float wanted_value)
{
	angle = wanted_value;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle = -2 * PI;
	return (angle);
}

void	check_distance(t_ray *ray)
{
	if (ray->dist_v < ray->dist_h)
	{
		ray->ray_x = ray->hit_x_ver;
		ray->ray_y = ray->hit_y_ver;
		ray->dist_real = ray->dist_v;
		ray->map_x = ray->ver_map_x;
		ray->map_y = ray->ver_map_y;
		ray->cast_color = 0xFF0000FF;
	}
	else
	{
		ray->ray_x = ray->hit_x_hor;
		ray->ray_y = ray->hit_y_hor;
		ray->dist_real = ray->dist_h;
		ray->map_x = ray->hor_map_x;
		ray->map_y = ray->hor_map_y;
		ray->cast_color = 0xAB0213FF;
	}
}
