/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:00:34 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 23:29:17 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	convert_colors(t_data *data)
{
	char	**f;
	char	**c;

	if (check_comma(data->fileinfo.f + 1) || check_comma(data->fileinfo.c + 1))
		print_error(data, INVALID_COLORS);
	f = ft_split(data->fileinfo.f + 1, ',');
	c = ft_split(data->fileinfo.c + 1, ',');
	if (!f || !c || f[3] != NULL || c[3] != NULL)
		free_tab_error(data, f, c);
	if (check_rgb(f) || check_rgb(c))
		free_tab_error(data, f, c);
	if (rgb_to_hexa(&data->fileinfo.f_hex, ft_atoi(f[0]),
			ft_atoi(f[1]), ft_atoi(f[2]))
		|| rgb_to_hexa(&data->fileinfo.c_hex, ft_atoi(c[0]),
			ft_atoi(c[1]), ft_atoi(c[2])))
		free_tab_error(data, f, c);
	free_tab(c);
	free_tab(f);
}

void	malloc_map(t_data *data, int i, int len)
{
	int	j;

	j = 0;
	data->map = malloc(sizeof(char *) * (i + 1));
	while (j < i)
	{
		data->map[j] = malloc(sizeof(char) * (len + 1));
		j++;
	}
	data->map_lenght = len;
	data->map_height = i;
}

void	get_map_size(t_data *data)
{
	t_file	*tmp;
	int		i;
	int		len;

	i = 0;
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
	malloc_map(data, i, len);
	data->file = tmp;
}

void	copy_map_info(t_data *data, int i, int j)
{
	data->map[j][i] = data->file->line[i];
	if (data->map[j][i] == 'N' || data->map[j][i] == 'S' ||
		data->map[j][i] == 'E' || data->map[j][i] == 'W')
	{
		get_player_pos(data, j, i);
		data->map[j][i] = '0';
	}
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
				copy_map_info(data, i, j);
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
