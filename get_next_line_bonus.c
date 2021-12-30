/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:25:16 by ekeen-wy          #+#    #+#             */
/*   Updated: 2021/12/30 19:49:47 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*
the last if condition is to check whether all characters in buf are copied
to output or there are still some characters that are carried over.
*/
static char	*gnl_output(char **str)
{
	char			*output;
	char			*temp;
	unsigned int	len;
	unsigned int	index;

	if (!*str)
		return (NULL);
	temp = *str;
	len = ft_strlen(*str);
	if (!ft_strchr(*str, '\n'))
	{
		output = gnl_substr(*str, 0, len);
		*str = NULL;
		free(temp);
		return (output);
	}
	index = ft_strlen(ft_strchr(*str, '\n'));
	output = gnl_substr(*str, 0, len - index + 1);
	if (len == ft_strlen(output))
		*str = NULL;
	else
		*str = ft_strjoin("", ft_strchr(*str, '\n') + 1);
	free(temp);
	return (output);
}

static char	*gnl_read(int fd, char **str, char *buf)
{
	int		bytes_read;
	char	*temp;

	if (!*str || !ft_strchr(*str, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		while (bytes_read > 0)
		{
			buf[bytes_read] = '\0';
			if (!*str)
				*str = ft_strjoin("", buf);
			else
			{
				temp = *str;
				*str = ft_strjoin(temp, buf);
				free(temp);
			}
			if (ft_strchr(buf, '\n') == NULL)
				bytes_read = read(fd, buf, BUFFER_SIZE);
			else
				break ;
		}
	}
	free(buf);
	return (gnl_output(str));
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	if (read(fd, buf, 0) == -1)
	{
		free(buf);
		return (NULL);
	}
	return (gnl_read(fd, &str[fd], buf));
}
