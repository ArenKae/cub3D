/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:40:48 by acosi             #+#    #+#             */
/*   Updated: 2024/03/05 01:43:00 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char	*msg, int status)
{
	if (msg == NULL)
		exit(status);
	perror(msg);
	exit(status);
}

void	print_error(int msg)
{
	if (msg == INVALID_FILE)
		ft_putstr_fd("Error\nInvalid file.\n", 2);
	if (msg == INVALID_FILE)
		ft_putstr_fd("Error\nInvalid colors.\n", 2);
	exit (EXIT_FAILURE);
}

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