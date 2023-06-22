/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@marvin.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:44:12 by mjouot            #+#    #+#             */
/*   Updated: 2022/10/30 16:44:30 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../INCLUDES/libft.h"
#include <unistd.h>

void	ft_putendl(char *s)
{
	if (s != 0)
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
