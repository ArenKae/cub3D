/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:40:48 by acosi             #+#    #+#             */
/*   Updated: 2024/03/04 22:34:22 by acosi            ###   ########.fr       */
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
	exit (EXIT_FAILURE);
}
