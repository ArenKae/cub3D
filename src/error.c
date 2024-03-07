/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:33:00 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 23:28:19 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	if (msg == OPEN_ERROR)
		ft_putstr_fd(RED "Error\nCould not open file.\n"STOP, 2);
	if (msg != INVALID_NAME)
		free_all(data);
	exit (EXIT_FAILURE);
}

void	free_tab_error(t_data *data, char **F, char **C)
{
	free_tab(F);
	free_tab(C);
	print_error(data, INVALID_COLORS);
}

void	free_and_error(t_data *data, char *s1, char *s2)
{
	free(s1);
	free(s2);
	print_error(data, INVALID_FILE);
}
