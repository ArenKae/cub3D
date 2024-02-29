/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/02/29 05:27:48 by acosi            ###   ########.fr       */
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
	{
		data->player_pos.x += (cos(data->player_pos.angle) / 5);
		data->player_pos.y -= (sin(data->player_pos.angle) / 5);
	}
	if (keycode == 115)
	{
		data->player_pos.x -= (cos(data->player_pos.angle) / 5);
		data->player_pos.y += (sin(data->player_pos.angle) / 5);
	}
	if (keycode == 100)
	{
		data->player_pos.x += (sin(data->player_pos.angle) / 5);
		data->player_pos.y += (cos(data->player_pos.angle) / 5);
	}
	if (keycode == 97 || keycode == 113)
	{
		data->player_pos.x -= (sin(data->player_pos.angle) / 5);
		data->player_pos.y -= (cos(data->player_pos.angle) / 5);
	}
	if (keycode == 65363)
	{
		data->player_pos.angle = data->player_pos.angle - (2.5 * M_PI / 180);
		if (data->player_pos.angle >= M_PI * 2)
			data->player_pos.angle = 0;
	}
	if (keycode == 65361)
	{
		data->player_pos.angle = data->player_pos.angle + (2.5 * M_PI / 180);
		if (data->player_pos.angle <= 0)
			data->player_pos.angle = M_PI * 2;
	}
	if (data->player_pos.angle > M_PI * 2)
		data->player_pos.angle = 2.5 * M_PI / 180;
	if (data->player_pos.angle < 2.4 * M_PI / 180)
		data->player_pos.angle = M_PI * 2;
	raycast(data);
	return (0);
}

void	hooks_handler(t_data *data)
{
	mlx_hook(data->win, KeyPress, KeyPressMask, key_press, data);
}


int	main(int ac, char **av)
{
	(void)av;
	t_data	data;
	data.map = malloc(sizeof(char *) * 9);
	data.map[0] = strdup("11111111");
 	data.map[1] = strdup("10000001");
 	data.map[2] = strdup("10000001");
 	data.map[3] = strdup("10000001");
 	data.map[4] = strdup("10000111");
 	data.map[5] = strdup("10010001");
 	data.map[6] = strdup("10000001");
 	data.map[7] = strdup("10000001");
 	data.map[8] = strdup("11111111");

	data.player_pos.x = 5;
	data.player_pos.y = 5;
	data.player_pos.angle = M_PI / 180;
	data.value = 0;
	data.frames = 0;
	data.i = 0;
	if (ac == 2)
	{
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
		//mlx_loop_hook(data.mlx, raycast, &data);
		// mlx_key_hook(data.window, on_key, &data);
		// mlx_loop_hook(data.mlx, init_patrol, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}