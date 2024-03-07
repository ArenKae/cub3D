/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:58:54 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:17:36 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab)
{
	int	i;

	i = -1;
	if (tab == NULL)
		return ;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_file_info(t_data *data)
{
	if (data->fileinfo.no)
		free(data->fileinfo.no);
	if (data->fileinfo.so)
		free(data->fileinfo.so);
	if (data->fileinfo.ea)
		free(data->fileinfo.ea);
	if (data->fileinfo.we)
		free(data->fileinfo.we);
	if (data->fileinfo.f)
		free(data->fileinfo.f);
	if (data->fileinfo.c)
		free(data->fileinfo.c);
}

void	free_all(t_data *data)
{
	free_file_info(data);
	free_tab(data->map);
	if (data->text)
		free(data->text);
}

void	free_and_error(t_data *data, char **F, char **C)
{
	free_tab(F);
	free_tab(C);
	print_error(data, INVALID_COLORS);
}

int	destroy_window(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		mlx_destroy_image(data->mlx, data->text[i].ptr);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_all(data);
	exit(EXIT_SUCCESS);
}

void	free_mlx(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4 && data->text[i].ptr)
		mlx_destroy_image(data->mlx, data->text[i].ptr);
	mlx_destroy_image(data->mlx, data->img.ptr);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
}
