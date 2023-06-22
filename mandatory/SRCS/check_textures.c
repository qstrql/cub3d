/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 12:29:38 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/15 12:56:10 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	verify_texture_path(t_game *data)
{
	if (file_exist(data->config.no) == false)
		return (FAIL);
	if (file_exist(data->config.so) == false)
		return (FAIL);
	if (file_exist(data->config.ea) == false)
		return (FAIL);
	if (file_exist(data->config.we) == false)
		return (FAIL);
	return (SUCCESS);
}
