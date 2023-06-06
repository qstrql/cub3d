/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbertaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:39:22 by lbertaux          #+#    #+#             */
/*   Updated: 2023/05/31 17:39:23 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

t_rgb	get_rgb_value(t_rc_texture texture, int x, int y)
{
	return (texture.pixels[y * texture.width + x]);
}

t_rgb	*texture_to_rgb_array_img(mlx_image_t *texture)
{
	unsigned int	i;
	int				j;
	t_rgb			*ret;

	i = 0;
	j = 0;
	ret = ft_calloc(texture->width * texture->height + 1, sizeof(t_rgb));
	while (i < texture->width * texture->height * 4)
	{
		if (j == 0)
			ret[i / 4].r = texture->pixels[i];
		else if (j == 1)
			ret[i / 4].g = texture->pixels[i];
		else if (j == 2)
			ret[i / 4].b = texture->pixels[i];
		else if (j == 3)
		{
			ret[i / 4].a = texture->pixels[i];
			j = -1;
		}
		i++;
		j++;
	}
	ret[i / 4].r = -1;
	return (ret);
}

t_rc_texture	*init_rc_texture(char *path, mlx_t *mlx)
{
	mlx_texture_t	*tmp_texture;
	mlx_image_t		*tmp_img;
	t_rc_texture	*ret;

	tmp_texture = mlx_load_png(path);
	if (tmp_texture == NULL)
		return (NULL);
	tmp_img = mlx_texture_to_image(mlx, tmp_texture);
	mlx_resize_image(tmp_img, TEXTURE_WIDTH, TEXTURE_HEIGHT);
	ret = ft_calloc(1, sizeof(t_rc_texture));
	ret->pixels = texture_to_rgb_array_img(tmp_img);
	ret->width = tmp_img->width;
	ret->height = tmp_img->height;
	mlx_delete_image(mlx, tmp_img);
	mlx_delete_texture(tmp_texture);
	return (ret);
}

void	free_rc_texture(t_rc_texture *texture)
{
	free(texture->pixels);
	free(texture);
}

int32_t	color_int32(t_rgb rgb)
{
	return (ft_pixel(rgb.r, rgb.g, rgb.b, rgb.a));
}
