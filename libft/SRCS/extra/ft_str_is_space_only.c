/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_space_only.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:03:45 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/02 00:04:13 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../INCLUDES/libft.h"

bool str_is_space_only(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (true);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}

