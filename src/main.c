/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 22:48:59 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*window_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx,
			800, 600, "Cub3d");
	return (data->win);
}

void	init_structures(t_data *data)
{
	data->fileinfo.no = NULL;
	data->fileinfo.so = NULL;
	data->fileinfo.ea = NULL;
	data->fileinfo.we = NULL;
	data->fileinfo.f = NULL;
	data->fileinfo.c = NULL;
	data->fileinfo.f_hex = 0;
	data->fileinfo.c_hex = 0;
	data->fileinfo.n = 0;
	data->fileinfo.s = 0;
	data->fileinfo.e = 0;
	data->fileinfo.w = 0;
	data->move = 0;
	data->rotate = 0;
	data->parse.map_flag = 0;
	data->parse.pos_flag = 0;
	data->parse.n = 0;
	data->parse.s = 0;
	data->parse.e = 0;
	data->parse.w = 0;
	data->parse.f = 0;
	data->parse.c = 0;
	data->text = NULL;
	data->map = NULL;
	data->clock = 0;
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 1)
		return (printf(RED "Error\nPlease select a valid map.\n" STOP));
	if (ac == 2)
	{
		init_structures(&data);
		check_map_name(&data, av[1]);
		init_map(&data, av[1]);
		data.mlx = mlx_init();
		if (!data.mlx)
			return (EXIT_FAILURE);
		window_init(&data);
		data.img.ptr = mlx_new_image(data.mlx, 800, 600);
		data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.pixel_bits,
				&data.img.size_line, &data.img.endian);
		render_texture(&data);
		hooks_handler(&data);
		mlx_hook(data.win, DestroyNotify, KeyReleaseMask,
			destroy_window, &data);
		mlx_loop_hook(data.mlx, game, &data);
		mlx_loop(data.mlx);
	}
	printf(RED "Error\nToo many arguments.\n" STOP);
	return (EXIT_SUCCESS);
}
