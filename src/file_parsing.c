/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:21 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 17:15:10 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	store_info(t_data *data, char *line)
{
	char	*tmp;

	tmp = trim_spaces(line);
	if (line == NULL || tmp[0] == '\n' || tmp[0] == '\0')
		return (free(tmp));
	check_format_path(tmp, "NO", &data->fileinfo.n);
	check_format_path(tmp, "SO", &data->fileinfo.s);
	check_format_path(tmp, "EA", &data->fileinfo.e);
	check_format_path(tmp, "WE", &data->fileinfo.w);
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
	{
		free(tmp);
		free(line);
		print_error(data, INVALID_FILE);
	}
	free(tmp);
	if (multiple_infos(data))
	{
		free(line);
		print_error(data, INVALID_FILE);
	}
}

int	read_texture(t_data *data, int fd)
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
	free(line);
	data->file->next = NULL;
	data->file = tmp;
	if (data->parse.map_flag != 3)
		return (1);
	return (0);
}

void	convert_colors(t_data *data)
{
	char	**f;
	char	**c;

	if (check_comma(data->fileinfo.f + 1) || check_comma(data->fileinfo.c + 1))
		print_error(data, INVALID_COLORS);
	f = ft_split(data->fileinfo.f + 1, ',');
	c = ft_split(data->fileinfo.c + 1, ',');
	if (!f || !c || f[3] != NULL || c[3] != NULL)
		free_and_error(data, f, c);
	if (check_rgb(f) || check_rgb(c))
		free_and_error(data, f, c);
	if (rgb_to_hexa(&data->fileinfo.f_hex, ft_atoi(f[0]),
			ft_atoi(f[1]), ft_atoi(f[2]))
		|| rgb_to_hexa(&data->fileinfo.c_hex, ft_atoi(c[0]),
			ft_atoi(c[1]), ft_atoi(c[2])))
		free_and_error(data, f, c);
	free_tab(c);
	free_tab(f);
}

void	get_map_size(t_data *data)
{
	t_file	*tmp;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	tmp = data->file;
	while (data->file->next)
	{
		if (data->file->line[0] && data->file->line[0] != '\n')
		{
			if ((int)ft_strlen(data->file->line) > len)
				len = (ft_strlen(data->file->line) - 1);
			i++;
		}
		data->file = data->file->next;
	}
	data->map = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		data->map[j] = malloc(sizeof(char) * (len + 1));
		j++;
	}
	data->map_lenght = len;
	data->map_height = i;
	data->file = tmp;
}

void	get_player_pos(t_data *data, int y, int x)
{
	data->parse.pos_flag += 1;
	data->player_pos.x = x + 0.5;
	data->player_pos.y = y + 0.5;
	data->player_pos.angle = (int_ft_strchr("ENWS", data->map[y][x]) * 1.5708);
}

void	fill_map(t_data *data)
{
	int		i;
	int		j;
	t_file	*tmp;

	j = 0;
	tmp = data->file;
	while (data->file->next)
	{
		if (data->file->line[0] != '\n')
		{
			i = 0;
			while (data->file->line[i] && data->file->line[i] != '\n')
			{
				data->map[j][i] = data->file->line[i];
				if (data->map[j][i] == 'N' || data->map[j][i] == 'S' ||
					data->map[j][i] == 'E' || data->map[j][i] == 'W')
				{
					get_player_pos(data, j, i);
					data->map[j][i] = '0';
				}
				i++;
			}
			data->map[j][i] = '\0';
			j++;
		}
		data->file = data->file->next;
	}
	data->map[j] = NULL;
	data->file = tmp;
}

void	init_map(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("open", EXIT_FAILURE));
	if (!read_texture(data, fd))
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
