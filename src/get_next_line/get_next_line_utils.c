/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:38:40 by keschouf          #+#    #+#             */
/*   Updated: 2023/04/01 02:12:51 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	free(s1);
	j = 0;
	while (s2[j] != '\0')
	{
		dest[i] = s2[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	static char	*str;

	str = malloc(sizeof(*s) * (len + 1));
	if (!str)
	{
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			str[j] = s[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*ft_strdup(char *src)
{
	int		i;
	char	*str;

	i = ft_strlen(src);
	if (!(str = ((char *)malloc(sizeof(*str) * i + 1))))
	{
		return (NULL);
	}
	i = 0;
	while (src[i] != '\0')
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';	
	return (str);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t size;

	size = 0;
	if (dst || src)
	{
		while (size < n)
		{
			((unsigned char *)dst)[size] = ((unsigned char *)src)[size];
			size++;
		}
		return (dst);
	}
	return (NULL);
}

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char	*t1;
	char	*t2;

	t1 = (char *)src;
	t2 = (char *)dst;
	if (t1 < t2)
		while (n-- > 0)
		{
			t2[n] = t1[n];
		}
	else
		ft_memcpy(t2, t1, n);
	return (dst);
}
