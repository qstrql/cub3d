/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:25:28 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:25:29 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	fill_floor_rgb(t_config *config, char **tmp)
{
	config->floor.r = ft_atoi(tmp[0]);
	config->floor.g = ft_atoi(tmp[1]);
	config->floor.b = ft_atoi(tmp[2]);
	config->floor.a = 255;
	if (config->floor.r > 255 || config->floor.r < 0)
		return (FAIL);
	if (config->floor.g > 255 || config->floor.g < 0)
		return (FAIL);
	if (config->floor.b > 255 || config->floor.b < 0)
		return (FAIL);
	return (SUCCESS);
}

int	fill_ceiling_rgb(t_config *config, char **tmp)
{
	config->ceiling.r = ft_atoi(tmp[0]);
	config->ceiling.g = ft_atoi(tmp[1]);
	config->ceiling.b = ft_atoi(tmp[2]);
	config->ceiling.a = 255;
	if (config->ceiling.r > 255 || config->ceiling.r < 0)
		return (FAIL);
	if (config->ceiling.g > 255 || config->ceiling.g < 0)
		return (FAIL);
	if (config->ceiling.b > 255 || config->ceiling.b < 0)
		return (FAIL);
	return (SUCCESS);
}

int	get_rbg(t_config *config, char **line)
{
	char	**tmp;
	int		ret;

	ret = FAIL;
	if (check_for_correct_rgb(line[1]) == FAIL)
		return (ret);
	tmp = ft_split(line[1], ',');
	if (str_array_len(tmp) != 3)
	{
		free_split_array(&tmp);
		return (ret);
	}
	if (ft_strncmp(line[0], "F", 2))
		ret = fill_floor_rgb(config, tmp);
	if (ft_strncmp(line[0], "C", 2))
		ret = fill_ceiling_rgb(config, tmp);
	free_split_array(&tmp);
	return (ret);
}
