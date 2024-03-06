/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:21 by acosi             #+#    #+#             */
/*   Updated: 2024/03/06 03:14:55 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*trim_spaces(const char* line)
{
	char	*str;
    int		len;
    int		i;
	int		j;
    
	i = -1;
	j = 0;
    len = strlen(line);
	while (++i < len)
	{
		if (line[i] != ' ' && line[i] != '\t'
		&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
            j++;
	}
    str = (char*)malloc(sizeof(char) * (j + 1));
    if (!str)
		return (NULL);
    j = 0;
	i = -1;
	while (++i < len)
	{
		if (line[i] != ' ' && line[i]!= '\t'
		&& line[i] != '\v' && line[i] != '\f' && line[i] != '\r')
            str[j++] = line[i];
	}
	
    str[j - 1] = '\0';
    return str;
}

void	check_format_path(char *path, char *side, int *SIDE)
{
	if (path[0] == side[0] && path[1] == side[1])
	{
		if (path[2] == '.' && path[3] == '/')
			*SIDE = 4;
		else
			*SIDE = 2;
	}
}

void	malloc_info_2(t_data *data, char *tmp, char c)
{
	if (c == 'F')
	{
		data->fileinfo.F = ft_strdup(tmp);
		data->parse.F++;
	}
	if (c == 'C')
	{
		data->fileinfo.C = ft_strdup(tmp);
		data->parse.C++;
	}
}

void	malloc_info(t_data *data, char *tmp, char c)
{
	if (c == 'N')
	{
		data->fileinfo.NO = ft_strdup(tmp);
		data->parse.N++;
	}
	if (c == 'S')
	{
		data->fileinfo.SO = ft_strdup(tmp);
		data->parse.S++;
	}
	if (c == 'E')
	{
		data->fileinfo.EA = ft_strdup(tmp);
		data->parse.E++;
	}
	if (c == 'W')
	{
		data->fileinfo.WE = ft_strdup(tmp);
		data->parse.W++;
	}
	else
	malloc_info_2(data, tmp, c);
}

int	multiple_infos(t_data *data)
{
	if (data->parse.N > 1 || data->parse.S > 1 || 
		data->parse.E > 1 || data->parse.W > 1 || 
		data->parse.F > 1 || data->parse.C > 1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	store_info(t_data *data, char *line)
{
	char	*tmp;
	
	if (line == NULL || trim_spaces(line)[0] == '\n' || trim_spaces(line)[0] == '\0')
		return ;
	tmp = trim_spaces(line);
	check_format_path(tmp, "NO", &data->fileinfo.N);
	check_format_path(tmp, "SO", &data->fileinfo.S);
	check_format_path(tmp, "EA", &data->fileinfo.E);
	check_format_path(tmp, "WE", &data->fileinfo.W);
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
		print_error(data, INVALID_FILE);
	}
	free(tmp);
	if (multiple_infos(data))
		print_error(data, INVALID_FILE);
}

int	missing_info(t_data *data)
{
	if (!data->fileinfo.NO || !data->fileinfo.SO || !data->fileinfo.EA
		|| !data->fileinfo.WE  || !data->fileinfo.F || !data->fileinfo.C)
		return (1);
	return (0);
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
	tmp = data->file;
	line = get_next_line(fd);
	while (line)
	{
		data->file->line = line;
		if (line && line[0] != '\n' && data->parse.map_flag == 0)
			data->parse.map_flag = 1;
		else if (line && line[0] == '\n' && data->parse.map_flag == 1)
			data->parse.map_flag = 2;
		line = get_next_line(fd);
		data->file->next = malloc(sizeof(t_file));
		data->file = data->file->next;
	}
	data->file->next = NULL;
	data->file = tmp;
	if (data->parse.map_flag == 1)
		return (1);
	return (0);
}

int	check_rgb(char **rgb) {
    int	i;
	int	j;
	
	i = 0;
    while (rgb[i] != NULL)
	{
		j = 0;
        while (rgb[i][j] != '\0')
		{
            if (!char_isdigit(rgb[i][j]))
                return (EXIT_FAILURE);
            j++;
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int	check_comma(char *str)
{
	int	i;

	i = 0;
	if (str[i] == ',')
		return (EXIT_FAILURE);
	i = -1;
	while (str[++i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (EXIT_FAILURE);
	}
	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == ',')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	convert_colors(t_data *data)
{
	char	**F;
	char	**C;
	
	if (check_comma(data->fileinfo.F + 1) || check_comma(data->fileinfo.C + 1))
		print_error(data, INVALID_COLORS);
	F = ft_split(data->fileinfo.F + 1, ',');
	C = ft_split(data->fileinfo.C + 1, ',');
	if (!F || !C || F[3] != NULL || C[3] != NULL)
		print_error(data, INVALID_COLORS);
	if (check_rgb(F) || check_rgb(C))
		print_error(data, INVALID_COLORS);
	if (rgb_to_hexa(&data->fileinfo.F_hex, ft_atoi(F[0]), ft_atoi(F[1]), ft_atoi(F[2]))
		|| rgb_to_hexa(&data->fileinfo.C_hex, ft_atoi(C[0]), ft_atoi(C[1]), ft_atoi(C[2])))
		print_error(data, INVALID_COLORS);
}

void	get_map_size(t_data *data)
{
	t_file *tmp;
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = 0;
	tmp = data->file;
	while (data->file->next)
	{
		if (data->file->line[0] != '\n')
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

void	fill_map(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->file->next)
	{
		if (data->file->line[0] != '\n')
		{
			i = 0;
			while (data->file->line[i] && data->file->line[i] != '\n')
			{
				data->map[j][i] = data->file->line[i];
				i++;
			}
			data->map[j][i] = '\0';
			j++;
		}
		data->file = data->file->next;
	}
	data->map[j] = NULL;
}

void	print_map(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		ft_putstr_fd(data->map[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	init_map(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("open", EXIT_FAILURE));
	if (!read_texture(data, fd))
		printf("error\n");
	get_map_size(data);
	fill_map(data);
	print_map(data);
	if (!check_map(data))
		printf("invalid map!\n");
	convert_colors(data);
}