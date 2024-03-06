/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:30:32 by acosi             #+#    #+#             */
/*   Updated: 2024/03/06 02:38:04 by acosi            ###   ########.fr       */
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