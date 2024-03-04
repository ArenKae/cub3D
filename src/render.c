/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/02/29 05:23:28 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void put_wall_pixel(t_data *data, int x, int y)
{
	int	i;
	int tmp;
	double	height;
	double	tmp_h;
	double	hit_pos2;
	int	tmp_v;
	int	temp;

	i = int_ft_strchr("NSEW", (int)data->wall.side);
	height = data->wall_h;
	tmp = floor(data->hit_pos);
	hit_pos2 = data->hit_pos;
	hit_pos2 = hit_pos2 - tmp;
	tmp_h = height / (data->text[i]->height);
	if (data->wall.side == 'W' || data->wall.side == 'S')
		hit_pos2 = 1 - hit_pos2;
	tmp_v = hit_pos2 * (data->text[i]->width);
	temp = (y - data->wall.top) / tmp_h;
	data->img.addr[y * 4 * WIN_L + x * 4 + 0] = data->text[i]->addr[temp * 4 * (data->text[i]->width) + tmp_v * 4 + 0];
	data->img.addr[y * 4 * WIN_L + x * 4 + 1] = data->text[i]->addr[temp * 4 * (data->text[i]->width) + tmp_v * 4 + 1];
	data->img.addr[y * 4 * WIN_L + x * 4 + 2] = data->text[i]->addr[temp * 4 * (data->text[i]->width) + tmp_v * 4 + 2];
	data->img.addr[y * 4 * WIN_L + x * 4 + 3] = data->text[i]->addr[temp * 4 * (data->text[i]->width) + tmp_v * 4 + 3];
}

void put_pixel(t_data *data, int x, int y, int pixel) // put the pixel
{
	if (pixel == -1)
	{
		put_wall_pixel(data, x, y);
		return ;
	}
	if (data->img.endian == 1)
	{
		data->img.addr[y * 4 * WIN_L + x * 4 + 0] = (pixel >> 24);
		data->img.addr[y * 4 * WIN_L + x * 4 + 1] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * WIN_L + x * 4 + 2] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * WIN_L + x * 4 + 4] = (pixel) & 0xFF;
	}
	else if (data->img.endian == 0)
	{
		data->img.addr[y * 4 * WIN_L + x * 4 + 0] = (pixel) & 0xFF;
		data->img.addr[y * 4 * WIN_L + x * 4 + 1] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * WIN_L + x * 4 + 2] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * WIN_L + x * 4 + 4] = (pixel >> 24);
	}
}


void put_wall(t_data *data, int ray, int top, int bot) // draw the wall
{
	int pixel;

	(void)pixel;
	//pixel = get_color(data);
	while (top < bot)
	{
		put_pixel(data, ray, top, -1);
		top++;
	}
	//printf(">>tpix = %d, bpix = %d\n", t_pix, b_pix);
}

void put_floor_and_ceil(t_data *data, int ray, int top, int bot) // draw the floor and the ceiling
{
	int i;

	i = 0;
	while (i < top)
	{
		put_pixel(data, ray, i, 0xB99470FF); // ceiling
		i++;
	}
	i = bot;
	while (i < WIN_H)
	{
		put_pixel(data, ray, i, 0x89CFF3FF); // floor
		i++;
	}
}

void render(t_data *data, int ray) // render the wall
{
	double	top;
	double	bot;

	data->wall_h = ((WIN_H / data->wall.distance) * 1.1) / 
		(cos(data->player_pos.angle - data->wall.ray_angle));
	top = (WIN_H / 2) - (data->wall_h / 2);
	bot = (WIN_H / 2) + (data->wall_h / 2);
	data->wall.top = top;
	data->wall.bot = bot;
	if (top < 0)
		top = 0;
	if (bot > WIN_H)
		bot = WIN_H;
	put_floor_and_ceil(data, ray, top, bot);
	put_wall(data, ray, top, bot);
}

