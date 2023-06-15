/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_content_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:18:55 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:18:56 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	remove_map_nl(t_mapinfo *map)
{
	int	i;

	i = map->height - 1;
	while (str_is_space_only(map->map[i]))
	{
		free(map->map[i]);
		map->map[i] = NULL;
		map->height--;
		i--;
	}
}

void	get_map(t_game *data, int i)
{
	int		j;
	int		max_len;

	max_len = 0;
	j = 0;
	while (data->raw_file[i])
	{
		while (str_is_space_only(data->raw_file[i])
			&& i < data->mapinfo->line_count - 1)
			i++;
		if (i >= data->mapinfo->line_count)
			break ;
		data->mapinfo->map[j] = ft_strdup(data->raw_file[i]);
		if ((int)ft_strlen(data->mapinfo->map[j]) > max_len)
			max_len = ft_strlen(data->mapinfo->map[j]);
		data->mapinfo->height++;
		j++;
		i++;
	}
	if (j == 0)
	{
		free(data->mapinfo->map);
		data->mapinfo->map = NULL;
	}
	data->mapinfo->width = max_len;
}

int	get_coord_path(t_config *config, char **line)
{
	if (ft_strncmp(line[0], "NO", 3) == 0 && !config->no)
		config->no = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "SO", 3) == 0 && !config->so)
		config->so = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "EA", 3) == 0 && !config->ea)
		config->ea = ft_strdup(line[1]);
	else if (ft_strncmp(line[0], "WE", 3) == 0 && !config->we)
		config->we = ft_strdup(line[1]);
	else
		return (FAIL);
	return (SUCCESS);
}

int	get_texture_rgb(t_config *config, char **line)
{
	int	ret;

	ret = FAIL;
	if (ft_strncmp(line[0], "F", 2) == 0)
		ret = get_rbg(config, line);
	else if (ft_strncmp(line[0], "C", 2) == 0)
		ret = get_rbg(config, line);
	else if (check_for_correct_coord(line[0]) == 1)
		ret = get_coord_path(config, line);
	else
		return (ret);
	return (ret);
}

int	get_content(t_game *data, int i)
{
	char	**tmp;
	char	*tmp_trim;

	tmp_trim = ft_strtrim(data->raw_file[i], " \t\n\r\f\v");
	free(data->raw_file[i]);
	data->raw_file[i] = ft_strdup(tmp_trim);
	free(tmp_trim);
	tmp = ft_split(data->raw_file[i], ' ');
	if (check_if_struct_filled(&data->config) == false)
	{
		if (str_array_len(tmp) != 2)
		{
			free_split_array(&tmp);
			return (INVALID_FILE);
		}
	}	
	if (get_texture_rgb(&data->config, tmp) == FAIL)
	{
		free_split_array(&tmp);
		return (INVALID_FILE);
	}
	free_split_array(&tmp);
	return (VALID_FILE);
}
