/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 15:50:23 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/04 16:57:34 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//#include "../INCLUDE/cub3d.h"
#include "cub3d.h"

int	check_line_start(char *str)
{
	int	i;
	int	ret;
	char **tmp;

	i = 0;
	ret = 0;
	tmp = ft_split(str, ' ');
	if (tmp[2])
	{
		free_split_array(&tmp);
		return (FAIL);
	}
	if (ft_strncmp(tmp[0], "NO", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp[0], "SO", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp[0], "EA", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp[0], "WE", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp[0], "F", 3) == 0)
		ret = 1;
	else if (ft_strncmp(tmp[0], "C", 3) == 0)
		ret = 1;
	printf("%d\n", ret);
	free_split_array(&tmp);
	return (ret);
}

int	check_file_content(t_data *data)
{
	int	i;

	i = 0;
	if (data->map.line_count < 9)
		return (INVALID_FILE);
	while (str_is_space_only(data->raw_file[i]))
		i++;
	if (check_line_start(data->raw_file[i]) == 0)
		return (FAIL);
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
