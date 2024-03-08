/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:31:49 by acosi             #+#    #+#             */
/*   Updated: 2024/03/08 11:22:47 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	malloc_info_2(t_data *data, char *tmp, char c)
{
	if (c == 'W')
	{
		if (data->fileinfo.we)
			free(data->fileinfo.we);
		data->fileinfo.we = ft_strdup(tmp);
		data->parse.w++;
	}
	if (c == 'F')
	{
		if (data->fileinfo.f)
			free(data->fileinfo.f);
		data->fileinfo.f = ft_strdup(tmp);
		data->parse.f++;
	}
	if (c == 'C')
	{
		if (data->fileinfo.c)
			free(data->fileinfo.c);
		data->fileinfo.c = ft_strdup(tmp);
		data->parse.c++;
	}
}

void	malloc_info(t_data *data, char *tmp, char c)
{
	if (c == 'N')
	{
		if (data->fileinfo.no)
			free(data->fileinfo.no);
		data->fileinfo.no = ft_strdup(tmp);
		data->parse.n++;
	}
	if (c == 'S')
	{
		if (data->fileinfo.so)
			free(data->fileinfo.so);
		data->fileinfo.so = ft_strdup(tmp);
		data->parse.s++;
	}
	if (c == 'E')
	{
		if (data->fileinfo.ea)
			free(data->fileinfo.ea);
		data->fileinfo.ea = ft_strdup(tmp);
		data->parse.e++;
	}
	else
		malloc_info_2(data, tmp, c);
}

void	check_format_path(t_data *data, char *tmp)
{
	get_format_path(tmp, "NO", &data->fileinfo.n);
	get_format_path(tmp, "SO", &data->fileinfo.s);
	get_format_path(tmp, "EA", &data->fileinfo.e);
	get_format_path(tmp, "WE", &data->fileinfo.w);
}

void	store_info(t_data *data, char *line)
{
	char	*tmp;

	tmp = trim_spaces(line);
	if (line == NULL || tmp[0] == '\n' || tmp[0] == '\0')
		return (free(tmp));
	check_format_path(data, tmp);
	if (tmp[0] == 'N' && tmp[1] == 'O')
		malloc_info(data, tmp, 'N');
	else if (tmp[0] == 'S' && tmp[1] == 'O')
		malloc_info(data, tmp, 'S');
	else if (tmp[0] == 'E' && tmp[1] == 'A')
		malloc_info(data, tmp, 'E');
	else if (tmp[0] == 'W' && tmp[1] == 'E')
		malloc_info(data, tmp, 'W');
	else if (tmp[0] == 'F')
		malloc_info(data, tmp, 'F');
	else if (tmp[0] == 'C')
		malloc_info(data, tmp, 'C');
	else
		free_and_error(data, tmp, line);
	if (multiple_infos(data))
		free_and_error(data, tmp, line);
	free(tmp);
}
