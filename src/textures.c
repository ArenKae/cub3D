/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 23:29:43 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_texture_data(t_data *data)
{
	int	i;

	i = -1;
	data->text = malloc(sizeof(t_img) * 4);
	if (!data->text)
		return (exit_error("malloc", EXIT_FAILURE));
	while (++i < 4)
	{
		data->text[i].ptr = NULL;
		data->text[i].addr = NULL;
		data->text[i].pixel_bits = 0;
		data->text[i].size_line = 0;
		data->text[i].endian = 0;
		data->text[i].width = 0;
		data->text[i].height = 0;
	}
}

char	**malloc_textures_index(t_data *data, char **index)
{
	index = malloc(sizeof(char *) * 5);
	if (!index)
		return (NULL);
	index[NORTH] = ft_strdup(data->fileinfo.no + data->fileinfo.n);
	index[SOUTH] = ft_strdup(data->fileinfo.so + data->fileinfo.s);
	index[EAST] = ft_strdup(data->fileinfo.ea + data->fileinfo.e);
	index[WEST] = ft_strdup(data->fileinfo.we + data->fileinfo.w);
	index[4] = NULL;
	return (index);
}

void	create_textures(t_data *data)
{
	int		i;
	char	**index;

	i = -1;
	index = NULL;
	init_texture_data(data);
	index = malloc_textures_index(data, index);
	if (index == NULL)
		return (exit_error("malloc", EXIT_FAILURE));
	while (++i < 4)
	{
		data->text[i].ptr = mlx_xpm_file_to_image(data->mlx, index[i],
				&data->text[i].width, &data->text[i].height);
		if (data->text[i].ptr == NULL)
		{
			free_tab(index);
			free_mlx(data);
			print_error(data, INVALID_TEXTURES);
		}
		data->text[i].addr = mlx_get_data_addr(data->text[i].ptr,
				&data->text[i].pixel_bits, &data->text[i].size_line,
				&data->text[i].endian);
	}
	free_tab(index);
}

void	render_texture(t_data *data)
{
	create_textures(data);
}
