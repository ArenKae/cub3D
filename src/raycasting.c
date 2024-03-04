/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/03/04 22:18:02 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		data->player_pos.angle = data->player_pos.angle - (1 * M_PI / 180);
		if (data->player_pos.angle >= M_PI * 2)
			data->player_pos.angle = 0;
	}
	if (data->rotate == 2)
	{
		data->player_pos.angle = data->player_pos.angle + (1 * M_PI / 180);
		if (data->player_pos.angle <= 0)
			data->player_pos.angle = M_PI * 2;
	}
	if (data->player_pos.angle > M_PI * 2)
		data->player_pos.angle = 2.5 * M_PI / 180;
	if (data->player_pos.angle < 2.4 * M_PI / 180)
		data->player_pos.angle = M_PI * 2;
}

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

int hit(double x, double y, t_data *data) // check the wall hit
{
    int  x_map;
    int  y_map;
    int  x2_map;
    int  y2_map;

    if (x <= 1 || y <= 1)
        return (1);
    if (x > 8 || y > 8)
        return (1);
    x_map = floor(x);
    y_map = floor(y);
    x2_map = floor(x - 0.000001);
    y2_map = floor(y - 0.000001);
    if (data->map[y_map] && x_map <= (int)strlen(data->map[y_map]))
    {
        if (data->map[y_map][x_map] == '1')
            return (1);
        else if (data->map[y2_map][x2_map] == '1')
            return (1);
    }
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


float get_h_inter(t_data *data, double *x_impact)
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

float get_v_inter(t_data *data, double *y_impact)
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
	while (!hit(data->inter.x, data->inter.y, data))
	{
		data->inter.x += data->inter.x_step;
		data->inter.y += data->inter.y_step;
	}
	*y_impact = data->inter.y;
	return (sqrt(pow(data->inter.x - data->player_pos.x, 2) + pow(data->inter.y - data->player_pos.y, 2)));
}


void	raycast(t_data *data)
{
	double	h_inter;
	double	v_inter;
	int		ray;
	int		flag;
	double	x_impact;
	double	y_impact;


	double ray_inter;
	ray_inter = 0.001091;
	ray = -1;
	flag = 0;
	if (floor(data->player_pos.x) == data->player_pos.x) //prevent vertical distorsion for round x values
		data->player_pos.x -= 0.000001;
	data->wall.ray_angle = data->player_pos.angle + 0.516600;
	if (data->wall.ray_angle >= M_PI * 2)
		data->wall.ray_angle -= M_PI * 2;
	while (++ray < WIN_L)
	{
		flag = 0;
		if (ray < 300)
			ray_inter += 0.000001;
		else if (ray > 500)
			ray_inter -= 0.000001;
		data->wall.ray_angle -= ray_inter;
		if (data->wall.ray_angle == 0)
			data->wall.ray_angle = 0.000001; //prevent segfault if angle=0 (no tangent)
		if (data->wall.ray_angle < 0)
			data->wall.ray_angle += M_PI * 2;
		h_inter = get_h_inter(data, &x_impact);
		v_inter = get_v_inter(data, &y_impact);
		if (v_inter <= h_inter)
		{
			data->wall.distance = v_inter;
			get_wall_side(data, data->wall.ray_angle, flag);
			data->hit_pos = y_impact;
		}
		else
		{
			flag = 1;
			data->wall.distance = h_inter;
			get_wall_side(data, data->wall.ray_angle, flag);
			data->hit_pos = x_impact;
		}
		ray++;
		render(data, ray);
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
}

int	game(t_data *data)
{
	player_movement(data);
	player_rotation(data);
	raycast(data);
	return (1);
}