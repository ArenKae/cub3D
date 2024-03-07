#include "cub3d.h"

void	player_movement(t_data *data)
{
	if (data->move == 1)
	{
		data->player_pos.x += (cos(data->player_pos.angle) / 30);
		data->player_pos.y -= (sin(data->player_pos.angle) / 30);
	}
	else if (data->move == 2)
	{
		data->player_pos.x -= (cos(data->player_pos.angle) / 30);
		data->player_pos.y += (sin(data->player_pos.angle) / 30);
	}
	else if (data->move == 3)
	{
		data->player_pos.x += (sin(data->player_pos.angle) / 30);
		data->player_pos.y += (cos(data->player_pos.angle) / 30);
	}
	else if (data->move == 4)
	{
		data->player_pos.x -= (sin(data->player_pos.angle) / 30);
		data->player_pos.y -= (cos(data->player_pos.angle) / 30);
	}
}

void	player_rotation(t_data *data)
{
	if (data->rotate == 1)
	{
		data->player_pos.angle = data->player_pos.angle - (2 * M_PI / 180);
		if (data->player_pos.angle >= M_PI * 2)
			data->player_pos.angle = 0;
	}
	if (data->rotate == 2)
	{
		data->player_pos.angle = data->player_pos.angle + (2 * M_PI / 180);
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
