/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/02/24 15:02:40 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_texture_data(t_context *context)
{
	int	i;
	
	i = -1;
	context->text = malloc(sizeof(t_img *) * 4 + sizeof(t_img) * 4);
	if (!context->text)
		return (exit_error(0));
	t_img *img_array = (t_img *)(context->text + 4);
	while(++i < 4)
	{
		context->text[i] = &img_array[i];
		context->text[i]->addr = NULL;
		context->text[i]->addr = NULL;
		context->text[i]->pixel_bits = 0;
		context->text[i]->size_line = 0;
		context->text[i]->endian = 0;
	}
}

char	**malloc_textures_index(char **index)
{
	index = malloc(sizeof(char *) * 4);
	if (!index)
		return (NULL);
	index[NORTH] = "textures/north.xpm\0";
	index[SOUTH] = "textures/south.xpm\0";
	index[EAST] = "textures/east.xpm\0";
	index[WEST] = "textures/west.xpm\0";
	index[4] = NULL;
	return (index);
}

void	create_textures(t_context *context)
{
	int		i;
	char	**index;
	
	i = -1;
	index = NULL;
	init_texture_data(context);
	index = malloc_textures_index(index);
	while (++i < 4)
	{
		context->text[i]->ptr = mlx_xpm_file_to_image(context->game, index[i],
			&context->text[i]->width, &context->text[i]->height);
		if (context->text[i]->ptr == NULL)
			return (exit_error(0));
		context->text[i]->addr = mlx_get_data_addr(context->text[i]->ptr,
			&context->text[i]->pixel_bits, &context->text[i]->size_line, &context->text[i]->endian);
	}
	free(index);
}

void	render(t_context *context)
{
	int	i;
	
	i = 0;
	create_textures(context);
	mlx_put_image_to_window(context->game, context->window, context->text[i]->ptr, 50, 50);
}