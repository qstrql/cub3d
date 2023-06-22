/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:46:43 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:46:43 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	ft_printf_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("%s\n", strs[i]);
		i++;
	}
}

void	debugprint(t_game *data)
{
	if (data)
	{
		if (data->config.no)
			printf("%s\n", data->config.no);
		if (data->config.so)
			printf("%s\n", data->config.so);
		if (data->config.we)
			printf("%s\n", data->config.we);
		if (data->config.ea)
			printf("%s\n", data->config.ea);
		if (data->config.ceiling.r != -1)
		{
			printf("%d\n", data->config.ceiling.r);
			printf("%d\n", data->config.ceiling.g);
			printf("%d\n", data->config.ceiling.b);
		}
		if (data->config.floor.r != -1)
		{
			printf("%d\n", data->config.floor.r);
			printf("%d\n", data->config.floor.g);
			printf("%d\n", data->config.floor.b);
		}
		if (data->mapinfo->map)
			ft_printf_strs(data->mapinfo->map);
	}
}

void	print_map(t_mapinfo *map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	printf("map height : %d\n", map->height);
	while (i < map->height)
	{
		while (map->map[i][j])
		{
			printf("%c,", map->map[i][j]);
			j++;
		}
		j = 0;
		i++;
		printf("\n");
	}
}
