/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_space_only.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:03:45 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/23 12:50:20 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../INCLUDES/libft.h"

bool	str_is_space_only(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (true);
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (false);
		i++;
	}
	return (true);
}
