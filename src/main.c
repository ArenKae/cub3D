/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:16:35 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*window_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx,
			800, 600, "Cub3d");
	return (data->win);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 27 || keycode == 65307)
		destroy_window(data);
	if (keycode == 119 || keycode == 122)
		data->move = 1;
	else if (keycode == 115)
		data->move = 2;
	else if (keycode == 100)
		data->move = 3;
	else if (keycode == 97 || keycode == 113)
		data->move = 4;
	else if (keycode == 65363)
		data->rotate = 1;
	else if (keycode == 65361)
		data->rotate = 2;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 119 || keycode == 122)
		data->move = 0;
	else if (keycode == 115)
		data->move = 0;
	else if (keycode == 100)
		data->move = 0;
	else if (keycode == 97 || keycode == 113)
		data->move = 0;
	else if (keycode == 65363)
		data->rotate = 0;
	else if (keycode == 65361)
		data->rotate = 0;
	return (0);
}

void	hooks_handler(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
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
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)av;
	data.value = 0;
	data.frames = 0;
	data.clock = 0;
	if (ac == 2)
	{
		check_map_name(&data, av[1]);
		init_structures(&data);
		init_map(&data, av[1]);
		data.mlx = mlx_init();
		if (!data.mlx)
			return (1);
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
	return (0);
}
