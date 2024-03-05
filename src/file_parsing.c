/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:21 by acosi             #+#    #+#             */
/*   Updated: 2024/03/05 03:44:48 by acosi            ###   ########.fr       */
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

void	store_info(t_data *data, char *line)
{
	char	*tmp;
	
	if (line == NULL || trim_spaces(line)[0] == '\n' || trim_spaces(line)[0] == '\0')
		return ;
	tmp = trim_spaces(line);
	if (tmp[0] == 'N' && tmp[1] == 'O')
		data->fileinfo.NO = ft_strdup(tmp);
	else if (tmp[0] == 'S' && tmp[1] == 'O')
		data->fileinfo.SO = ft_strdup(tmp);
	else if (tmp[0] == 'E' && tmp[1] == 'A')
		data->fileinfo.EA = ft_strdup(tmp);
	else if (tmp[0] == 'W' && tmp[1] == 'E')
		data->fileinfo.WE = ft_strdup(tmp);
	else if (tmp[0] == 'F')
		data->fileinfo.F = ft_strdup(tmp);
	else if (tmp[0] == 'C')
		data->fileinfo.C = ft_strdup(tmp);
	else
		print_error(INVALID_FILE);
	free(tmp);
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
	
	while (missing_info(data))
	{
		line = get_next_line(fd);
		store_info(data, line);
		free(line);
	}
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
		print_error(WRONG_COLORS);
	F = ft_split(data->fileinfo.F + 1, ',');
	C = ft_split(data->fileinfo.C + 1, ',');
	if (!F || !C || F[3] != NULL || C[3] != NULL)
		print_error(WRONG_COLORS);
	if (check_rgb(F) || check_rgb(C))
		print_error(WRONG_COLORS);
	if (rgb_to_hexa(&data->fileinfo.F_hex, ft_atoi(F[0]), ft_atoi(F[1]), ft_atoi(F[2]))
		|| rgb_to_hexa(&data->fileinfo.C_hex, ft_atoi(C[0]), ft_atoi(C[1]), ft_atoi(C[2])))
		print_error(WRONG_COLORS);
}

void	init_map(t_data *data, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("open", EXIT_FAILURE));
	read_texture(data, fd);
	convert_colors(data);
}
