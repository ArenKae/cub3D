/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:40:48 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:44:50 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	rgb_to_hexa(int *hex, int r, int g, int b)
{
	int	color;

	if (r > 255 || g > 255 || b > 255)
		return (EXIT_FAILURE);
	if (r < 0 || g < 0 || b < 0)
		return (EXIT_FAILURE);
	color = (r << 16) | (g << 8) | b;
	color |= 0xFF << 24;
	*hex = color;
	return (EXIT_SUCCESS);
}

int	char_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

void	init_iterator(int *i, int *j)
{
	*i = -1;
	*j = 0;
}

char	*trim_spaces(const char *line)
{
	char	*str;
	int		len;
	int		i;
	int		j;

	init_iterator(&i, &j);
	len = strlen(line);
	while (++i < len)
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			j++;
	}
	str = (char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	init_iterator(&i, &j);
	while (++i < len)
	{
		if (line[i] != ' ' && line[i] != '\t'
			&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
			str[j++] = line[i];
	}
	str[j - 1] = '\0';
	return (str);
}
