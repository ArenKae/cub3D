/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keschouf <keschouf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 06:41:30 by keschouf          #+#    #+#             */
/*   Updated: 2023/03/01 12:26:07 by keschouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"
#include <stdio.h>
#include <limits.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strchr(const char *s, int c)
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
	line = ft_substr(*str, 0, pos);
	len = ft_strlen((*str) + pos);
	if (len != 0)
		ft_memmove(*str, (*str) + pos, len + 1);
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

	tmp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		buff[BUFFER_SIZE + 1];
	static char	*str[OPEN_MAX];
	int			ret;
	int			pos;

	if (str[fd])
	{
		pos = ft_strchr(str[fd], '\n');
		if (pos >= 0)
			return (cut_line(&str[fd], pos));
	}
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (ret <= 0 && !str[fd])
			return (0);
		buff[ret] = '\0';
		str[fd] = ft_strjoin(str[fd], buff);
		pos = ft_strchr(str[fd], '\n');
		if (pos != -1)
			return (cut_line(&str[fd], pos));
	}
	return (no_new_line(&str[fd]));
}
