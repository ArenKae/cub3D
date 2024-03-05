/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 22:30:32 by acosi             #+#    #+#             */
/*   Updated: 2024/03/05 22:35:12 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Checks that the first argument passed to the program begins 
	with map/.
*/

int	check_map_name_2(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

/*
	Checks that the first argument passed to the program is a valid
	.ber file located in the map/ directory.
	s1 = av[1] and s2 = ".ber"
*/

int	check_map_name(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (s1[i] == s2[j])
		{
			j++;
			i++;
			if (s2[j] == '\0' && i == ft_strlen(s1))
				if (ft_strlen(s1) - ft_strlen("/map") > 4)
					return (1);
		}
		i++;
	}
	return (print_error(3));
}