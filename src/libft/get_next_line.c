/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:38:27 by keschouf          #+#    #+#             */
/*   Updated: 2024/03/04 22:37:31 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*dest;

	if (!s1)
		return (gnl_strdup(s2));
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

char	*gnl_substr(char const *s, unsigned int start, size_t len)
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

char	*gnl_strdup(char *src)
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

void	*gnl_memcpy(void *dst, const void *src, size_t n)
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

void	*gnl_memmove(void *dst, const void *src, size_t n)
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
		gnl_memcpy(t2, t1, n);
	return (dst);
}

int	int_ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] != (char)c)
		return (-1);
	return (i);
}

char	*cut_line(char **str, int pos)
{
	int		len;
	char	*line;

	pos++;
	line = gnl_substr(*str, 0, pos);
	len = ft_strlen((*str) + pos);
	if (len != 0)
		gnl_memmove(*str, (*str) + pos, len + 1);
	else
	{
		free(*str);
		*str = NULL;
	}
	return (line);
}

char	*no_new_line(char **str)
{	
	char	*tmp;

	tmp = gnl_strdup(*str);
	free(*str);
	*str = NULL;
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*str;
	int			ret;
	int			pos;

	if (str)
	{	
		pos = int_ft_strchr(str, '\n');
		if (pos >= 0)
			return (cut_line(&str, pos));
	}
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0 && !str)
			return (0);
		buff[ret] = '\0';
		str = gnl_strjoin(str, buff);
		pos = int_ft_strchr(str, '\n');
		if (pos != -1)
			return (cut_line(&str, pos));
	}
	return (no_new_line(&str));
}
