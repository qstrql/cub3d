/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:33:20 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:33:21 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	verify_player_present(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (j < data->mapinfo->width && data->mapinfo->map[i][j])
		{
			if (ft_strchr("NSWE", data->mapinfo->map[i][j]))
				return (SUCCESS);
			j++;
		}
		j = 0;
		i++;
	}
	return (FAIL);
}

int	verify_map_characters(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height)
	{
		while (data->mapinfo->map[i][j])
		{
			if (ft_strchr("10DWNSE \n\t\r\f\v", data->mapinfo->map[i][j]) == 0)
				return (FAIL);
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

