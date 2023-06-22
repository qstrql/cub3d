/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:23:16 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:23:18 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

bool	check_if_struct_filled(t_config *config)
{
	if (config->no == NULL || config->so == NULL || config->we == NULL
		|| config->ea == NULL || config->floor.r == -1
		|| config->ceiling.r == -1)
	{
		return (false);
	}
	else
		return (true);
}

int	check_for_correct_coord(char *coord)
{
	if (ft_strncmp(coord, "NO", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "SO", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "EA", 3) == 0)
		return (1);
	else if (ft_strncmp(coord, "WE", 3) == 0)
		return (1);
	else
		return (0);
}

int	check_for_correct_rgb(char *rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		if (!ft_isdigit(rgb[i]) && rgb[i] != ',')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
