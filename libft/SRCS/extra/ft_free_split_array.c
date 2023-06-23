/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 00:04:44 by mjouot            #+#    #+#             */
/*   Updated: 2023/06/23 12:51:17 by lbertaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../INCLUDES/libft.h"

void	free_split_array(char ***array)
{
	int	i;

	i = 0;
	if (*array == NULL)
		return ;
	while ((*array)[i] != NULL)
	{
		better_free((*array)[i]);
		i++;
	}
	free((*array)[i]);
	better_free(*array);
}
