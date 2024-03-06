/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/03/06 00:02:23 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*window_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx,
			WIN_L, WIN_H, "Cub3d");
	return (data->win);
}

// int	key_press(int keycode, t_data *data)
// {
// 	if (keycode == 27 || keycode == 65307)
// 		destroy_window(data);
// 	if (keycode == 119 || keycode == 122)
// 	{
// 		data->player_pos.x += (cos(data->player_pos.angle) / 5);
// 		data->player_pos.y -= (sin(data->player_pos.angle) / 5);
// 		data->move = 1;
// 	}
// 	if (keycode == 115)
// 	{
// 		data->player_pos.x -= (cos(data->player_pos.angle) / 5);
// 		data->player_pos.y += (sin(data->player_pos.angle) / 5);
// 	}
// 	if (keycode == 100)
// 	{
// 		data->player_pos.x += (sin(data->player_pos.angle) / 5);
// 		data->player_pos.y += (cos(data->player_pos.angle) / 5);
// 	}
// 	if (keycode == 97 || keycode == 113)
// 	{
// 		data->player_pos.x -= (sin(data->player_pos.angle) / 5);
// 		data->player_pos.y -= (cos(data->player_pos.angle) / 5);
// 	}
// 	if (keycode == 65363)
// 	{
// 		data->player_pos.angle = data->player_pos.angle - (2.5 * M_PI / 180);
// 		if (data->player_pos.angle >= M_PI * 2)
// 			data->player_pos.angle = 0;
// 	}
// 	if (keycode == 65361)
// 	{
// 		data->player_pos.angle = data->player_pos.angle + (2.5 * M_PI / 180);
// 		if (data->player_pos.angle <= 0)
// 			data->player_pos.angle = M_PI * 2;
// 	}
// 	if (data->player_pos.angle > M_PI * 2)
// 		data->player_pos.angle = 2.5 * M_PI / 180;
// 	if (data->player_pos.angle < 2.4 * M_PI / 180)
// 		data->player_pos.angle = M_PI * 2;
// 	return (0);
// }

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
	if (keycode == 27 || keycode == 65307)
		destroy_window(data);
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
	// mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	// raycast(data);
}

void	init_structures(t_data *data)
{
	data->fileinfo.NO = NULL;
	data->fileinfo.SO = NULL;
	data->fileinfo.EA = NULL;
	data->fileinfo.WE = NULL;
	data->fileinfo.F = NULL;
	data->fileinfo.C = NULL;
	data->fileinfo.F_hex = 0;
	data->fileinfo.C_hex = 0;
	data->move = 0;
	data->rotate = 0;
	data->parse.map_flag = 0;
}

int	main(int ac, char **av)
{
	(void)av;
	t_data	data;
	data.player_pos.x = 2;
	data.player_pos.y = 2;
	data.player_pos.angle = M_PI / 180;
	data.value = 0;
	data.frames = 0;
	data.clock = 0;
	if (ac == 2)
	{
		check_map_name(av[1]);
		init_structures(&data);
		init_map(&data, av[1]);
		data.mlx = mlx_init();
		if (!data.mlx)
			return (1);
		window_init(&data);
		data.img.ptr = mlx_new_image(data.mlx, WIN_L, WIN_H);
		data.img.addr = mlx_get_data_addr(data.img.ptr, &data.img.pixel_bits,
			&data.img.size_line, &data.img.endian);
		render_texture(&data);
		// raycast(&data);
		hooks_handler(&data);
		mlx_hook(data.win, DestroyNotify, KeyReleaseMask,
			destroy_window, &data);
		mlx_loop_hook(data.mlx, game, &data);
		// mlx_key_hook(data.window, on_key, &data);
		// mlx_loop_hook(data.mlx, init_patrol, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}