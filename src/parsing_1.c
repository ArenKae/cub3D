/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:21 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 18:32:39 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_map(t_data *data, int fd, char *line)
{
	while (line)
	{
		data->file->line = ft_strdup(line);
		if (line && line[0] != '\n' && data->parse.map_flag == 0)
			data->parse.map_flag = 1;
		else if (line && line[0] == '\n' && data->parse.map_flag == 1)
			data->parse.map_flag = 2;
		else if (line && line[0] != '\n' && data->parse.map_flag == 2)
			data->parse.map_flag = 3;
		if (line)
			free(line);
		line = get_next_line(fd);
		data->file->next = malloc(sizeof(t_file));
		data->file = data->file->next;
		data->file->line = NULL;
	}
}

int	read_file(t_data *data, int fd)
{
	char	*line;
	t_file	*tmp;

	while (missing_info(data))
	{
		line = get_next_line(fd);
		if (!line)
			print_error(data, INVALID_FILE);
		store_info(data, line);
		free(line);
	}
	data->file = malloc(sizeof(t_file));
	data->file->line = NULL;
	tmp = data->file;
	line = get_next_line(fd);
	read_map(data, fd, line);
	data->file->next = NULL;
	data->file = tmp;
	if (data->parse.map_flag != 3)
		return (1);
	return (0);
}

void	init_map(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("open", EXIT_FAILURE));
	if (!read_file(data, fd))
	{
		free_list(data);
		print_error(data, INVALID_MAP);
	}
	get_map_size(data);
	fill_map(data);
	free_list(data);
	if (!check_map_init(data))
		print_error(data, INVALID_MAP);
	convert_colors(data);
}
