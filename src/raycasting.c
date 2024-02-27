/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/02/27 22:43:58 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_wall_side(t_data *data, double ray_angle, int flag) // get the color of the wall
{
	if (flag == 0)
	{
		if (ray_angle > (M_PI / 2) && ray_angle < (3 * M_PI) / 2)
			data->wall.side = 'E';
		else
			data->wall.side = 'W';
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			data->wall.side = 'S';
		else
			data->wall.side = 'N';
	}
}

int wall_hit(double x, double y, t_data *data) // check the wall hit
{
	int  x_map;
	int  y_map;

	if (x <= 1 || y <= 1)
		return (0);
	if (x > 8 || y > 8)
		return (0);
	x_map = floor(x);
	y_map = floor(y);
	if (data->map[y_map] && x_map <= (int)strlen(data->map[y_map]))
		if (data->map[y_map][x_map] == '1')
			return (0);
	return (1);
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


float get_h_inter(t_data *data, double *x_impact, double *y_impact)
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
	while (wall_hit(data->inter.x, data->inter.y, data))
	{
		data->inter.x += data->inter.x_step;
		data->inter.y += data->inter.y_step;
	}
	*x_impact = data->inter.x;
	*y_impact = data->inter.y;
	return (sqrt(pow(data->inter.x - data->player_pos.x, 2) + pow(data->inter.y - data->player_pos.y, 2)));
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

float get_v_inter(t_data *data, double *x_impact, double *y_impact)
{
	data->inter.x_step = 1; 
	data->inter.y_step = 1 * tan(data->wall.ray_angle);
	data->inter.x = data->player_pos.x;
	data->inter.y = data->player_pos.y;
	if (data->wall.ray_angle < (M_PI * 3 / 2) && data->wall.ray_angle > (M_PI / 2))
		data->inter.x_step = -1;
	if ((data->wall.ray_angle > 0 && data->wall.ray_angle < M_PI && data->inter.y_step > 0) || ((data->wall.ray_angle > M_PI && data->inter.y_step < 0)))
	{
		data->inter.y_step *= -1;
	}
	get_first_v_inter(data);
	while (wall_hit(data->inter.x, data->inter.y, data))
	{
		data->inter.x += data->inter.x_step;
		data->inter.y += data->inter.y_step;
	}
	*x_impact = data->inter.x;
	*y_impact = data->inter.y;
	return (sqrt(pow(data->inter.x - data->player_pos.x, 2) + pow(data->inter.y - data->player_pos.y, 2)));
}


void	raycast(t_data *data)
{
	double	h_inter;
	double	v_inter;
	int		ray;
	double	distance;
	int		flag;
	double	x_impact;
	double	y_impact;

	ray = 0;
	flag = 0;
	(void)flag;
	(void)distance;
	(void)h_inter;
	data->wall.ray_angle = data->player_pos.angle - 0.523599;
	if (data->wall.ray_angle < 0)
		data->wall.ray_angle = M_PI * 2 + data->wall.ray_angle;
	while (ray < 800)
	{
		if (data->wall.ray_angle >= M_PI * 2)
			data->wall.ray_angle = 0;
		flag = 0;
		if (data->wall.ray_angle == 0)
			data->wall.ray_angle = 0.000001; //prevent segfault if angle=0 (no tangent)
		h_inter = get_h_inter(data, &x_impact, &y_impact);
		v_inter = get_v_inter(data, &x_impact, &y_impact);
		data->wall.ray_angle += 0.001309;
		if (v_inter <= h_inter)
		{
			data->wall.distance = v_inter;
			get_wall_side(data, data->wall.ray_angle, flag);
		}
		else
		{
			flag = 1;
			data->wall.distance = h_inter;
			get_wall_side(data, data->wall.ray_angle, flag);
		}
		ray++;
		render_wall(data, ray);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}
