/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:19:39 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:19:57 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
