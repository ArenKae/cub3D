/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:30:32 by acosi             #+#    #+#             */
/*   Updated: 2024/03/08 13:04:14 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*
	Checks if a file named only ".cub" is used.
*/

int	unamed_cub(char *str)
{
	int	i;
	
	i = ft_strlen(str);
	if (i > 4 && str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' && str[i - 4] == '.' && str[i - 5] == '/')
		return (1);
	else if (i == 4 && str[i - 1] == 'b' && str[i - 2] == 'u' && str[i - 3] == 'c' && str[i - 4] == '.')
		return (1);
	return (0);
}

/*
	Checks that the first argument passed to 
	the program is a valid.cub file.
*/

int	check_map_name(t_data *data, char *map)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	j = 0;
	str = ".cub";
	if (unamed_cub(map))
	{
		print_error(data, INVALID_NAME);
		return (EXIT_FAILURE);
	}
	while (map[i])
	{
		while (map[i] == str[j])
		{
			j++;
			i++;
			if (str[j] == '\0' && i == ft_strlen(map))
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
