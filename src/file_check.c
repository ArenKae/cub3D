/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:56:55 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 18:17:43 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Checks if all required infos in the file 
	have been found (textures and colors).
*/

int	missing_info(t_data *data)
{
	if (!data->fileinfo.no || !data->fileinfo.so || !data->fileinfo.ea
		|| !data->fileinfo.we || !data->fileinfo.f || !data->fileinfo.c)
		return (1);
	return (0);
}

/*
	If the counter for a file info is greater than 1, it means it has
	been parsed multiple times and there are redundant infos in the file.
*/

int	multiple_infos(t_data *data)
{
	if (data->parse.n > 1 || data->parse.s > 1
		|| data->parse.e > 1 || data->parse.w > 1
		|| data->parse.f > 1 || data->parse.c > 1)
		return (1);
	return (0);
}

/*
	Check if the texture path begins with "./" or not to get
	the right malloc size later.
*/
void	get_format_path(char *path, char *side, int *malloc)
{
	if (path[0] == side[0] && path[1] == side[1])
	{
		if (path[2] == '.' && path[3] == '/')
			*malloc = 4;
		else
			*malloc = 2;
	}
}

/*
	Checks if the file colors are only digits.
*/

int	check_rgb(char **rgb)
{
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

/*
	Because the colors in the file are stored with a ft_split() around the ',' 
	character, we have to explicitely check for invalid comas configurations in 
	the file (multiple consecutive ',' or ',' at the start or end of the string).
*/

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
