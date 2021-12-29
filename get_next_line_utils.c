/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeen-wy <ekeen-wy@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/27 13:34:46 by ekeen-wy          #+#    #+#             */
/*   Updated: 2021/12/28 21:59:51 by ekeen-wy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*ptr;
	unsigned int	len;
	unsigned int	i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	i = 0;
	if (ptr == NULL)
		return (NULL);
	while (*s1 != '\0')
		ptr[i++] = *s1++;
	while (*s2 != '\0')
		ptr[i++] = *s2++;
	*(ptr + len) = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		*temp;

	i = ft_strlen(s);
	temp = (char *) s;
	while (i + 1 != 0)
	{
		if (*temp == (char) c)
			return ((char *) temp);
		temp++;
		i--;
	}
	return (NULL);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*node;
	char	*copy_str;

	node = (t_list *)malloc(sizeof(t_list));
	copy_str = ft_strjoin("", content);
	if (node == NULL)
		return (NULL);
	node -> content = copy_str;
	node -> next = NULL;
	return (node);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*check_last;

	check_last = *lst;
	while (check_last != NULL)
	{
		if (check_last -> next == NULL)
			break ;
		check_last = check_last -> next;
	}
	check_last -> next = new;
}
