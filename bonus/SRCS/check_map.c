/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:31:27 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:31:29 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	verify_map_left(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (data->mapinfo->map[i][j] && j < data->mapinfo->width
			&& ft_isspace(data->mapinfo->map[i][j]))
			j++;
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	verify_map_right(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(data->mapinfo->map[i]) - 1;
	while (i < data->mapinfo->height && data->mapinfo->map[i])
	{
		while (data->mapinfo->map[i][j] && j > 1
			&& ft_isspace(data->mapinfo->map[i][j]))
			j--;
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		i++;
		if (i < data->mapinfo->height && data->mapinfo->map[i])
			j = ft_strlen(data->mapinfo->map[i]) - 1;
	}
	return (SUCCESS);
}

int	verify_map_up(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < data->mapinfo->width - 1)
	{
		while (data->mapinfo->map[i][j] && ft_isspace(data->mapinfo->map[i][j]))
		{
			if (data->mapinfo->map[i + 1] != NULL
				&& (int)ft_strlen(data->mapinfo->map[i + 1]) < j)
				break ;
			else
				return (FAIL);
			i++;
		}
		if (data->mapinfo->map[i][j] && data->mapinfo->map[i][j] != '1')
			return (FAIL);
		i = 0;
		j++;
	}
	return (SUCCESS);
}

int	verify_map_down(t_game *data)
{
	int	i;
	int	j;

	i = data->mapinfo->height - 1;
	j = 0;
	while (j < data->mapinfo->width - 1)
	{
		while (i > 1)
		{
			if ((int)ft_strlen(data->mapinfo->map[i]) - 1 < j)
				i--;
			else if (ft_isspace(data->mapinfo->map[i][j]))
				i--;
			else
				break ;
		}
		if (data->mapinfo->map[i][j] != '1')
			return (FAIL);
		i = data->mapinfo->height - 1;
		j++;
	}
	return (SUCCESS);
}

int	verify_map_validity(t_game *data)
{
	if (data->mapinfo->map == NULL)
		return (FAIL);
	if (verify_map_left(data) == FAIL)
		exit_msg(data, "cub3d: Map is missing wall on left side");
	if (verify_map_right(data) == FAIL)
		exit_msg(data, "cub3d: Map is missing wall on right side");
	if (verify_map_up(data) == FAIL)
		exit_msg(data, "cub3d: Map is missing wall on upper side");
	if (verify_map_down(data) == FAIL)
		exit_msg(data, "cub3d: Map is missing wall on lower side");
	if (data->mapinfo->height < 3 || data->mapinfo->width < 3)
		return (FAIL);
	return (SUCCESS);
}
