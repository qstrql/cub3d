/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:14:26 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:14:27 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	check_file_content(t_game *data)
{
	int		i;

	i = 0;
	while (data->raw_file[i] && check_if_struct_filled(&data->config) == false)
	{
		while (str_is_space_only(data->raw_file[i]))
			i++;
		if (get_content(data, i) == INVALID_FILE)
			return (INVALID_FILE);
		i++;
	}
	if (check_if_struct_filled(&data->config) == false)
		return (INVALID_FILE);
	else
	{
		data->mapinfo->height = 0;
		data->mapinfo->map = ft_calloc(data->mapinfo->line_count,
				sizeof(char *));
		get_map(data, i);
		remove_map_nl(data->mapinfo);
	}
	return (VALID_FILE);
}

int	parse_file(t_game *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_game(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		exit_msg(data, WRONG_FILE_CONTENT);
	if (verify_texture_path(data) == FAIL)
		exit_msg(data, WRONG_TEXTURE_PATH);
	if (verify_minimap_textures() == FAIL)
		exit_msg(data, MINIMAP_FILES_MISSING);
	if (verify_map_validity(data) == FAIL)
		exit_msg(data, BAD_MAP);
	if (verify_map_characters(data) == FAIL)
		exit_msg(data, BAD_CHARACTERS);
	return (VALID_FILE);
}

