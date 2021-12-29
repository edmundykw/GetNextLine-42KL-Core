/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:25:16 by ekeen-wy          #+#    #+#             */
/*   Updated: 2021/12/29 11:36:10 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*ptr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		ptr = (char *)malloc(sizeof(char));
		*ptr = '\0';
		return (ptr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (len-- > 0 && *(s + start) != '\0')
	{
		*(ptr + i) = *(char *)(s + start);
		start++;
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}

static char	*gnl_output(t_list **str, char *line)
{
	char			*output;
	char			*temp;
	t_list			*tempnode;

	output = gnl_substr(line, 0,
			ft_strlen(line) - ft_strlen(ft_strchr(line, '\n')) + 1);
	while (*str != NULL)
	{
		tempnode = *str;
		*str = tempnode -> next;
		free(tempnode -> content);
		free(tempnode);
	}
	temp = gnl_substr(line,
			ft_strlen(line) - ft_strlen(ft_strchr(line, '\n')) + 1,
			ft_strlen(ft_strchr(line, '\n')) - 1);
	*str = ft_lstnew(temp);
	free(temp);
	free(line);
	return (output);
}

static char	*gnl_process(t_list **str)
{
	char			*tempstr;
	char			*line;
	char			*clear_line;
	t_list			*tempnode;

	if (*str == NULL)
		return (NULL);
	tempnode = *str;
	tempstr = tempnode -> content;
	clear_line = NULL;
	if (tempnode -> next != NULL)
	{
		while (tempnode -> next != NULL)
		{
			tempnode = tempnode -> next;
			line = ft_strjoin(tempstr, tempnode -> content);
			if (clear_line != NULL)
				free(clear_line);
			tempstr = line;
			clear_line = line;
		}
	}
	else
		line = ft_strjoin("", tempnode -> content);
	return (gnl_output(str, line));
}

static int	gnl_read(int fd, t_list **str, char *buf)
{
	unsigned int	bytes_read;
	t_list			*ptr;

	ptr = *str;
	if (!ptr || !ft_strchr(ptr -> content, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		while (bytes_read > 0)
		{
			buf[bytes_read] = '\0';
			if (!*str)
				*str = ft_lstnew(buf);
			else
				ft_lstadd_back(str, ft_lstnew(buf));
			if (ft_strchr(buf, '\n') != NULL)
				break ;
			bytes_read = read(fd, buf, BUFFER_SIZE);
		}
	}
	free(buf);
	return (bytes_read);
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
	if (gnl_read(fd, &str, buf) == 0)
		return (NULL);
	return (gnl_process(&str));
}
