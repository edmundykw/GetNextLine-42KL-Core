/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:25:16 by ekeen-wy          #+#    #+#             */
/*   Updated: 2021/12/29 17:04:05 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	gnl_clear(t_list *str)
{
	t_list	*tempnode;

	while (str != NULL)
	{
		tempnode = str;
		str = tempnode -> next;
		free(tempnode -> content);
		free(tempnode);
	}
}

static char	*gnl_output(t_list **str)
{
	char			*line;
	t_list			*tempnode;
	unsigned int	i;
	unsigned int	j;

	if (!*str)
		return (NULL);
	tempnode = *str;
	i = ft_strlen(tempnode -> content);
	j = ft_strlen(ft_strchr(tempnode -> content, '\n'));
	line = gnl_substr(tempnode -> content, 0, i - j + 1);
	if (i == j + 1)
		*str = 0;
	else
		*str = ft_lstnew("", ft_strchr(tempnode -> content, '\n') + 1);
	gnl_clear(tempnode);
	return (line);
}

static void	gnl_read(int fd, t_list **str, char *buf)
{
	unsigned int	bytes_read;
	t_list			*ptr;

	ptr = *str;
	if (!*str || !ft_strchr(ptr -> content, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		while (bytes_read > 0)
		{
			buf[bytes_read] = '\0';
			if (!*str)
				*str = ft_lstnew("", buf);
			else
			{
				ptr = *str;
				*str = ft_lstnew(ptr -> content, buf);
				gnl_clear(ptr);
			}
			if (ft_strchr(buf, '\n') != NULL)
				break ;
			bytes_read = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
}

char	*get_next_line(int fd)
{
	static t_list	*str;
	char			*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	gnl_read(fd, &str, buf);
	return (gnl_output(&str));
}
