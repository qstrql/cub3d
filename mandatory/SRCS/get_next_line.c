/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjouot <mjouot@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:58:49 by mjouot            #+#    #+#             */
/*   Updated: 2023/05/01 18:19:41 by mjouot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

char	*ft_realloc(char *buf, char *line)
{
	char	*re_line;

	re_line = ft_strjoin(buf, line);
	free(buf);
	return (re_line);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i += 1;
	line = ft_calloc(i + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*ft_get_extra(char *str)
{
	int		i;
	int		len;
	char	*extra;

	len = ft_strlen(str);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	extra = ft_calloc((len - i) + 1, sizeof(char));
	i += 1;
	if (extra == NULL)
		return (NULL);
	len = 0;
	while (str[i + len] != '\0')
	{
		extra[len] = str[i + len];
		len++;
	}
	free(str);
	return (extra);
}

char	*ft_reader(char *buf, int fd)
{
	char	*line;
	ssize_t	size_read;

	size_read = 1;
	if (buf == NULL)
		buf = ft_calloc(1, sizeof(char));
	line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (line == NULL)
		return (NULL);
	while (ft_strchr(buf, '\n') == 0 && size_read > 0)
	{
		size_read = read(fd, line, BUFFER_SIZE);
		if (size_read == -1)
		{
			free(buf);
			free(line);
			return (NULL);
		}
		line[size_read] = '\0';
		buf = ft_realloc(buf, line);
	}
	free(line);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf = NULL;

	if (fd < 0)
		return (NULL);
	buf = ft_reader(buf, fd);
	if (buf == NULL)
		return (NULL);
	line = ft_get_line(buf);
	buf = ft_get_extra(buf);
	return (line);
}
