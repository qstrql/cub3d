/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/03 23:34:54 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int	check_file_content(t_data *data)
{
	if (data->map.line_count < 9)
		return (INVALID_FILE);
	//while(ignore empty lines)
	//if (ft_isprint && !ft_isdigit)
	//if (str[i] && str[i + 1])
	//if (check NSEW texture path)
	//if (check C/F RGB value)
	//fill data->map.map;
	return (VALID_FILE);
}

int	parse_file(t_data *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_program(data, INVALID_FILE);
	parse_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		return (free_data_struct(data, INVALID_FILE));
	return (VALID_FILE);
}

int main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(USAGE, EXIT_FAILURE));
	init_data_struct(&data);
	if (parse_file(&data, argv[1]) != VALID_FILE)
		return (INVALID_FILE);
	free_data_struct(&data, EXIT_SUCCESS);
}
