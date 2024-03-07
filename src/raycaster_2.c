#include "cub3d.h"

int	hit(double x, double y, t_data *data)
{
	int	x_map;
	int	y_map;
	int	x2_map;
	int	y2_map;

	if (x <= 1 || y <= 1)
		return (1);
	if (x >= data->map_lenght || y >= data->map_height)
		return (1);
	x_map = floor(x);
	y_map = floor(y);
	x2_map = floor(x - 0.000001);
	y2_map = floor(y - 0.000001);
	if (data->map[y_map][x_map] == '1' || data->map[y_map][x_map] == '\0')
		return (1);
	else if (data->map[y2_map][x2_map] == '1' ||
		data->map[y2_map][x2_map] == '\0')
		return (1);
	return (0);
}

void	get_first_h_inter(t_data *data)
{
	double	x_dif;
	double	y_dif;
	double	x_pos;
	double	y_pos;

	if (data->inter.y_step <= 0)
	{
		y_dif = data->inter.y - floor(data->inter.y);
		y_pos = data->inter.y - y_dif;
	}
	else
	{
		y_dif = ceil(data->inter.y) - data->inter.y;
		y_pos = data->inter.y + y_dif;
	}
	x_dif = data->inter.x_step * y_dif;
	x_pos = data->inter.x + x_dif;
	data->inter.x = x_pos;
	data->inter.y = y_pos;
}

float	get_h_inter(t_data *data, double *x_impact)
{
	data->inter.y_step = 1;
	data->inter.x_step = 1 / tan(data->wall.ray_angle);
	data->inter.x = data->player_pos.x;
	data->inter.y = data->player_pos.y;
	if (data->wall.ray_angle > M_PI)
		data->inter.x_step *= -1;
	if (data->wall.ray_angle > 0 && data->wall.ray_angle < M_PI)
		data->inter.y_step = -1;
	get_first_h_inter(data);
	while (!hit(data->inter.x, data->inter.y, data))
	{
		data->inter.x += data->inter.x_step;
		data->inter.y += data->inter.y_step;
	}
	*x_impact = data->inter.x;
	return (sqrt(pow(data->inter.x - data->player_pos.x, 2)
			+ pow(data->inter.y - data->player_pos.y, 2)));
}

void	get_first_v_inter(t_data *data)
{
	double	x_dif;
	double	y_dif;
	double	x_pos;
	double	y_pos;

	if (data->inter.x_step < 0)
	{
		x_dif = data->inter.x - floor(data->inter.x);
		x_pos = data->inter.x - x_dif;
	}
	else
	{
		x_dif = ceil(data->inter.x) - data->inter.x;
		x_pos = data->inter.x + x_dif;
	}
	y_dif = data->inter.y_step * x_dif;
	y_pos = data->inter.y + y_dif;
	data->inter.x = x_pos;
	data->inter.y = y_pos;
}

float	get_v_inter(t_data *data, double *y_impact)
{
	data->inter.x_step = 1;
	data->inter.y_step = 1 * tan(data->wall.ray_angle);
	data->inter.x = data->player_pos.x;
	data->inter.y = data->player_pos.y;
	if (data->wall.ray_angle < (M_PI * 3 / 2)
		&& data->wall.ray_angle > (M_PI / 2))
		data->inter.x_step = -1;
	if ((data->wall.ray_angle > 0 && data->wall.ray_angle
			< M_PI && data->inter.y_step > 0)
		|| ((data->wall.ray_angle > M_PI && data->inter.y_step < 0)))
	{
		data->inter.y_step *= -1;
	}
	get_first_v_inter(data);
	while (!hit(data->inter.x, data->inter.y, data))
	{
		data->inter.x += data->inter.x_step;
		data->inter.y += data->inter.y_step;
	}
	*y_impact = data->inter.y;
	return (sqrt(pow(data->inter.x - data->player_pos.x, 2)
			+ pow(data->inter.y - data->player_pos.y, 2)));
}
