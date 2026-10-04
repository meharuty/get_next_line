/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meharuty <meharuty@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 12:42:00 by meharuty          #+#    #+#             */
/*   Updated: 2026/03/19 11:14:48 by meharuty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_full_text(int fd, char *res)
{
	char	*tmp;
	char	*next_line;
	int		a;

	a = 0;
	while (!ft_strchr(res, '\n'))
	{
		next_line = get_the_line(fd, &a);
		if (!next_line)
		{
			if (a == -1)
			{
				free(res);
				return (NULL);
			}
			break ;
		}
		tmp = ft_strjoin(res, next_line);
		free(res);
		free(next_line);
		res = tmp;
	}
	return (res);
}

char	*get_my_line(char *res, int *i)
{
	char	*line;
	int		j;

	if (!res)
		return (NULL);
	while (res[(*i)] && res[*i] != '\n')
		(*i)++;
	line = malloc((*i) + 2);
	if (!line)
		return (NULL);
	j = 0;
	while (res[j] && res[j] != '\n')
	{
		line[j] = res[j];
		j++;
	}
	if (res[j] == '\n')
	{
		line[j] = res[j];
		j++;
		(*i)++;
	}
	line[j] = '\0';
	return (line);
}

char	*get_new_stat(char *res, int *i)
{
	int		j;
	int		len;
	char	*ret;

	j = 0;
	if (!res)
		return (NULL);
	len = ft_strlen(res);
	if (*i >= len)
	{
		free(res);
		return (NULL);
	}
	ret = malloc(len - (*i) + 1);
	if (!ret)
		return (NULL);
	while (res[(*i)])
		ret[j++] = res[(*i)++];
	ret[j] = '\0';
	free(res);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;
	int			i;

	i = 0;
	if (fd < 0)
	{
		free(res);
		return (NULL);
	}
	res = get_full_text(fd, res);
	if (!res)
		return (NULL);
	line = get_my_line(res, &i);
	res = get_new_stat(res, &i);
	return (line);
}
