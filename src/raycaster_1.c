/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 23:29:25 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	get_wall_side(t_data *data, double ray_angle, int flag)
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

void	raycast_angle(t_data *data, int ray, double *ray_inter)
{
	if (ray < 300)
		*ray_inter += 0.000001;
	else if (ray > 500)
		*ray_inter -= 0.000001;
	data->wall.ray_angle -= *ray_inter;
	if (data->wall.ray_angle == 0)
		data->wall.ray_angle = 0.000001;
	else if (data->wall.ray_angle == M_PI)
		data->wall.ray_angle -= 0.000001;
	else if (data->wall.ray_angle < 0)
		data->wall.ray_angle += M_PI * 2;
}

void	raycast(t_data *data, int flag, int ray, double ray_inter)
{
	double	h_inter;
	double	v_inter;
	double	x_impact;
	double	y_impact;

	while (++ray < 800)
	{
		flag = 0;
		raycast_angle(data, ray, &ray_inter);
		h_inter = get_h_inter(data, &x_impact);
		v_inter = get_v_inter(data, &y_impact);
		if (v_inter <= h_inter)
		{
			data->wall.distance = v_inter;
			data->hit_pos = y_impact;
		}
		else
		{
			flag = 1;
			data->wall.distance = h_inter;
			data->hit_pos = x_impact;
		}
		get_wall_side(data, data->wall.ray_angle, flag);
		render(data, ray);
	}
}

void	raycast_init(t_data *data)
{
	if (floor(data->player_pos.x) == data->player_pos.x)
		data->player_pos.x -= 0.000001;
	data->wall.ray_angle = data->player_pos.angle + 0.516600;
	if (data->wall.ray_angle >= M_PI * 2)
		data->wall.ray_angle -= M_PI * 2;
	raycast(data, 0, -1, 0.001091);
}

int	game(t_data *data)
{
	data->clock += 1;
	if (data->clock == 200)
	{
		player_movement(data);
		player_rotation(data);
		raycast_init(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img.ptr, 0, 0);
		data->clock = 0;
	}
	return (1);
}
