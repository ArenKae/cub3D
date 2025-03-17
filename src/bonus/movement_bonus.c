/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:57:34 by acosi             #+#    #+#             */
/*   Updated: 2025/03/17 22:53:26 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D_bonus.h"

int	valid_move_2(t_data *data, int i, int x_tmp, int y_tmp)
{
	if (i == 3)
	{
		x_tmp = (int)(data->player_pos.x + (sin(data->player_pos.angle) / 30));
		y_tmp = (int)(data->player_pos.y + (cos(data->player_pos.angle) / 30));
		if (data->map[y_tmp][x_tmp] == '\0' || data->map[y_tmp][x_tmp] == '1'
		|| x_tmp <= 0 || y_tmp <= 0 || x_tmp >= data->map_lenght
		|| y_tmp >= data->map_height)
			return (0);
	}
	if (i == 4)
	{
		x_tmp = (int)(data->player_pos.x - (sin(data->player_pos.angle) / 30));
		y_tmp = (int)(data->player_pos.y - (cos(data->player_pos.angle) / 30));
		if (data->map[y_tmp][x_tmp] == '\0' || data->map[y_tmp][x_tmp] == '1'
		|| x_tmp <= 0 || y_tmp <= 0 || x_tmp >= data->map_lenght
		|| y_tmp >= data->map_height)
			return (0);
	}
	return (1);
}

int	valid_move_1(t_data *data, int i, int x_tmp, int y_tmp)
{
	if (i == 1)
	{
		x_tmp = floor(data->player_pos.x + (cos(data->player_pos.angle) / 30));
		y_tmp = floor(data->player_pos.y - (sin(data->player_pos.angle) / 30));
		if (data->map[y_tmp][x_tmp] == '\0' || data->map[y_tmp][x_tmp] == '1'
			|| x_tmp <= 0 || y_tmp <= 0 || x_tmp >= data->map_lenght
			|| y_tmp >= data->map_height)
			return (0);
	}
	if (i == 2)
	{
		x_tmp = floor(data->player_pos.x - (cos(data->player_pos.angle) / 30));
		y_tmp = floor(data->player_pos.y + (sin(data->player_pos.angle) / 30));
		if (data->map[y_tmp][x_tmp] == '\0' || data->map[y_tmp][x_tmp] == '1'
		|| x_tmp <= 0 || y_tmp <= 0 || x_tmp >= data->map_lenght
		|| y_tmp >= data->map_height)
			return (0);
	}
	return (1);
}

void	player_movement(t_data *data)
{
	if (data->move == 1 && valid_move_1(data, data->move, 0, 0))
	{
		data->player_pos.x += (cos(data->player_pos.angle) / player_speed);
		data->player_pos.y -= (sin(data->player_pos.angle) / player_speed);
	}
	else if (data->move == 2 && valid_move_1(data, data->move, 0, 0))
	{
		data->player_pos.x -= (cos(data->player_pos.angle) / player_speed);
		data->player_pos.y += (sin(data->player_pos.angle) / player_speed);
	}
	else if (data->move == 3 && valid_move_2(data, data->move, 0, 0))
	{
		data->player_pos.x += (sin(data->player_pos.angle) / player_speed);
		data->player_pos.y += (cos(data->player_pos.angle) / player_speed);
	}
	else if (data->move == 4 && valid_move_2(data, data->move, 0, 0))
	{
		data->player_pos.x -= (sin(data->player_pos.angle) / player_speed);
		data->player_pos.y -= (cos(data->player_pos.angle) / player_speed);
	}
}

void	player_rotation(t_data *data)
{
	if (data->rotate == 1)
	{
		data->player_pos.angle = data->player_pos.angle - (camera_speed * M_PI / 180);
		if (data->player_pos.angle >= M_PI * 2)
			data->player_pos.angle = 0;
	}
	if (data->rotate == 2)
	{
		data->player_pos.angle = data->player_pos.angle + (camera_speed * M_PI / 180);
		if (data->player_pos.angle <= 0)
			data->player_pos.angle = M_PI * 2;
	}
	if (data->player_pos.angle > M_PI * 2)
	{
		data->player_pos.angle = 1 * M_PI / 180;
	}
	if (data->player_pos.angle < 0.9 * M_PI / 180)
	{
		data->player_pos.angle = M_PI * 2;
	}
}
