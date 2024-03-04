/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 22:19:21 by acosi             #+#    #+#             */
/*   Updated: 2024/03/04 22:56:50 by acosi            ###   ########.fr       */
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
	// if (data->fileinfo.NO)
	// 	printf("%s", data->fileinfo.NO);
	// if (data->fileinfo.SO)
	// 	printf("%s", data->fileinfo.SO);
	// if (data->fileinfo.EA)
	// 	printf("%s", data->fileinfo.EA);
	// if (data->fileinfo.WE)
	// 	printf("%s", data->fileinfo.WE);
	// if (data->fileinfo.F)
	// 	printf("%s", data->fileinfo.F);
	// if (data->fileinfo.C)
	// 	printf("%s", data->fileinfo.C);
	// printf("\n");
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

void	init_map(t_data *data, char *filename)
{
	int	fd;

	printf("%s\n", filename);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (exit_error("open", EXIT_FAILURE));
	read_texture(data, fd);
}