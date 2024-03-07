/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:58:54 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:35:08 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_file_info(t_data *data)
{
	if (data->fileinfo.no)
		free(data->fileinfo.no);
	if (data->fileinfo.so)
		free(data->fileinfo.so);
	if (data->fileinfo.ea)
		free(data->fileinfo.ea);
	if (data->fileinfo.we)
		free(data->fileinfo.we);
	if (data->fileinfo.f)
		free(data->fileinfo.f);
	if (data->fileinfo.c)
		free(data->fileinfo.c);
}

void	free_all(t_data *data)
{
	free_file_info(data);
	free_tab(data->map);
	if (data->text)
		free(data->text);
}

void	free_and_error(t_data *data, char **F, char **C)
{
	free_tab(F);
	free_tab(C);
	print_error(data, INVALID_COLORS);
}

void	free_list(t_data *data)
{
	t_file	*tmp;

	tmp = data->file;
	while (data->file)
	{
		if (data->file->line)
			free(data->file->line);
		tmp = data->file->next;
		free(data->file);
		data->file = tmp;
	}
}
