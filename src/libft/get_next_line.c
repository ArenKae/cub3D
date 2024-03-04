/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 19:38:27 by keschouf          #+#    #+#             */
/*   Updated: 2024/03/03 22:03:39 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		str = ft_strjoin(str, buff);
		pos = int_ft_strchr(str, '\n');
		if (pos != -1)
			return (cut_line(&str, pos));
	}
	return (no_new_line(&str));
}
