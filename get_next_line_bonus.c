/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharuty <meharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/12 16:45:13 by meharuty          #+#    #+#             */
/*   Updated: 2026/03/19 11:14:46 by meharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_the_line(int fd, int *a)
{
	int		bytes_read;
	char	*buffer;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == 0)
	{
		free(buffer);
		return (NULL);
	}
	if (bytes_read < 0)
	{
		*a = -1;
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*get_full_text(int fd, char *res[])
{
	char	*tmp;
	char	*next_line;
	int		a;

	a = 0;
	while (!ft_strchr(res[fd], '\n'))
	{
		next_line = get_the_line(fd, &a);
		if (!next_line)
		{
			if (a == -1)
			{
				free(res[fd]);
				return (NULL);
			}
			break ;
		}
		tmp = ft_strjoin(res[fd], next_line);
		free(res[fd]);
		free(next_line);
		res[fd] = tmp;
	}
	return (res[fd]);
}

char	*get_my_line(char *res[], int *i, int fd)
{
	char	*line;
	int		j;

	if (!res)
		return (NULL);
	while (res[fd][(*i)] && res[fd][*i] != '\n')
		(*i)++;
	line = malloc((*i) + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (res[fd][j] && res[fd][j] != '\n')
	{
		line[j] = res[fd][j];
		j++;
	}
	if (res[fd][j] == '\n')
	{
		line[j] = res[fd][j];
		j++;
		(*i)++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_new_stat(char *res[], int *i, int fd)
{
	int		j;
	int		len;
	char	*ret;

	j = 0;
	if (!res[fd])
	{
		return (NULL);
	}
	len = ft_strlen(res[fd]);
	if (*i >= len)
	{
		free(res[fd]);
		return (NULL);
	}
	ret = malloc(len - (*i) + 1);
	if (!ret)
		return (NULL);
	while (res[fd][(*i)])
		ret[j++] = res[fd][(*i)++];
	ret[j] = '\0';
	free(res[fd]);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*res[1024];
	char		*line;
	int			i;

	i = 0;
	if (fd < 0)
	{
		free(res[fd]);
		return (NULL);
	}
	res[fd] = get_full_text(fd, res);
	if (!res[fd])
		return (NULL);
	line = get_my_line(res, &i, fd);
	res[fd] = get_new_stat(res, &i, fd);
	return (line);
}
