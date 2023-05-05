/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/05 15:33:28 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int	get_line_content(t_data *data, int i, int j)
{
	return (EXIT_SUCCESS);	
}

int	check_file_content(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	if (data->map.line_count < 9)
		return (INVALID_FILE);
	while (data->raw_file[i])
	{
		while (str_is_space_only(data->raw_file[i]))
			i++;
		j = 0;
		while (data->raw_file[i][j])
		{
			get_line_content(data, i, j);
		}
	}
	//if (check NSEW texture path)
	//if (check C/F RGB value)
	//fill data->map.map;
	return (VALID_FILE);
}

int	parse_file(t_data *data, char *argv)
{
	if (parse_arg(argv) == FAIL)
		exit_program(data, INVALID_FILE);
	get_file_content(data, argv);
	if (check_file_content(data) == FAIL)
		exit_msg(data, "File content is wrong or missing");
	return (VALID_FILE);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error_msg(USAGE, EXIT_FAILURE));
	init_data_struct(&data);
	if (parse_file(&data, argv[1]) != VALID_FILE)
		return (INVALID_FILE);
	free_data_struct(&data, EXIT_SUCCESS);
}
