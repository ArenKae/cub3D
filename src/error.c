/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:00 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:33:29 by acosi            ###   ########.fr       */
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

void	print_error(t_data *data, int msg)
{
	if (msg == INVALID_NAME)
		ft_putstr_fd(RED "Error\nInvalid file name.\n"STOP, 2);
	if (msg == INVALID_FILE)
		ft_putstr_fd(RED "Error\nInvalid file.\n"STOP, 2);
	if (msg == INVALID_TEXTURES)
		ft_putstr_fd(RED "Error\nInvalid texture.\n"STOP, 2);
	if (msg == INVALID_COLORS)
		ft_putstr_fd(RED "Error\nInvalid color.\n"STOP, 2);
	if (msg == INVALID_MAP)
		ft_putstr_fd(RED "Error\nInvalid map.\n"STOP, 2);
	if (msg != INVALID_NAME)
		free_all(data);
	exit (EXIT_FAILURE);
}
