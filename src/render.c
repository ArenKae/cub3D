/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 16:06:08 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall_pixel(t_data *data, int x, int y, int i)
{
	double	height;
	double	tmp_h;
	double	hit_pos;
	int		tmp_v;
	int		tmp;

	height = data->wall_h;
	hit_pos = data->hit_pos - floor(data->hit_pos);
	tmp_h = height / (data->text[i].height);
	if (data->wall.side == 'W' || data->wall.side == 'S')
		hit_pos = 1 - hit_pos;
	tmp_v = hit_pos * (data->text[i].width);
	tmp = (y - data->wall.top) / tmp_h;
	data->img.addr[y * 4 * 800 + x * 4 + 0]
		= data->text[i].addr[tmp * 4 * (data->text[i].width) + tmp_v * 4 + 0];
	data->img.addr[y * 4 * 800 + x * 4 + 1]
		= data->text[i].addr[tmp * 4 * (data->text[i].width) + tmp_v * 4 + 1];
	data->img.addr[y * 4 * 800 + x * 4 + 2]
		= data->text[i].addr[tmp * 4 * (data->text[i].width) + tmp_v * 4 + 2];
	data->img.addr[y * 4 * 800 + x * 4 + 3]
		= data->text[i].addr[tmp * 4 * (data->text[i].width) + tmp_v * 4 + 3];
}

void	put_pixel(t_data *data, int x, int y, int pixel)
{
	if (pixel == -1)
	{
		put_wall_pixel(data, x, y, int_ft_strchr("NSEW", (int)data->wall.side));
		return ;
	}
	if (data->img.endian == 1)
	{
		data->img.addr[y * 4 * 800 + x * 4 + 0] = (pixel >> 24);
		data->img.addr[y * 4 * 800 + x * 4 + 1] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 2] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 3] = (pixel) & 0xFF;
	}
	else if (data->img.endian == 0)
	{
		data->img.addr[y * 4 * 800 + x * 4 + 0] = (pixel) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 1] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 2] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 3] = (pixel >> 24);
	}
}

void	draw_wall(t_data *data, int ray, int top, int bot)
{
	while (top < bot)
	{
		put_pixel(data, ray, top, -1);
		top++;
	}
}

void	put_floor_and_ceil(t_data *data, int ray, int top, int bot)
{
	int	i;

	i = 0;
	while (i < top)
	{
		put_pixel(data, ray, i, data->fileinfo.c_hex);
		i++;
	}
	i = bot;
	while (i < 600)
	{
		put_pixel(data, ray, i, data->fileinfo.f_hex);
		i++;
	}
}

void	render(t_data *data, int ray)
{
	double	top;
	double	bot;

	if (data->wall.distance <= 0.000001)
		data->wall.distance = 0.000001;
	data->wall_h = ((600 / data->wall.distance) * 1.1)
		/ cos(data->player_pos.angle - data->wall.ray_angle);
	top = (600 / 2) - (data->wall_h / 2);
	bot = (600 / 2) + (data->wall_h / 2);
	data->wall.top = top;
	data->wall.bot = bot;
	if (top < 0)
		top = 0;
	if (bot > 600)
		bot = 600;
	put_floor_and_ceil(data, ray, top, bot);
	draw_wall(data, ray, top, bot);
}
