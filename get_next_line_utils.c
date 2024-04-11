/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark <jpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:14:51 by joleal-b          #+#    #+#             */
/*   Updated: 2023/11/27 15:18:51 by joleal-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && (size - 1) > i)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = malloc(ft_strlen(s1) + ft_strlen(s2) * sizeof(char) + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i] = s2[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	array;
	char	*ptr;
	size_t	i;

	array = count * size;
	ptr = malloc(array);
	if (!ptr)
		return (NULL);
	i = 0;
	while (array > 0)
	{
		ptr[i] = 0;
		array--;
		i++;
	}
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	str_len;
	char	*substr;

	i = 0;
	str_len = ft_strlen(s);
	if (start > str_len)
		return (0);
	else if (len + start > str_len)
		substr = malloc(sizeof(char) * (str_len - start + 1));
	else
		substr = malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (i < len && start < str_len)
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[i] = '\0';
	return (substr);
}
