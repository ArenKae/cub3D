/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:30:32 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 17:58:18 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Checks that the first argument passed to 
	the program is a valid.cub file.
*/

int	check_map_name(t_data *data, char *map)
{
	size_t	i;
	size_t	j;
	char	*s2;

	i = 0;
	j = 0;
	s2 = ".cub";
	while (map[i])
	{
		while (map[i] == s2[j])
		{
			j++;
			i++;
			if (s2[j] == '\0' && i == ft_strlen(map))
				return (EXIT_SUCCESS);
		}
		i++;
	}
	print_error(data, INVALID_NAME);
	return (EXIT_FAILURE);
}

int	unclosed_map(t_data *data, char **map, int x, int y)
{
	if (y == 0 || x == 0)
		return (1);
	if (x == (data->map_lenght - 1) || y == (data->map_height - 1))
		return (1);
	if (!map[y - 1][x])
		return (1);
	else if (!map[y + 1][x])
		return (1);
	else if (!map[y][x - 1])
		return (1);
	else if (!map[y][x + 1])
		return (1);
	return (0);
}

int	check_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '0')
				if (unclosed_map(data, data->map, x, y))
					return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_map_init(t_data *data)
{
	if (data->parse.pos_flag != 1)
		return (0);
	if (check_map(data))
		return (1);
	return (0);
}
