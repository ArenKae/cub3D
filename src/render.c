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
	int tmp;
	double	height;
	double	tmp_h;
	double	hit_pos2;
	int	tmp_v;
	int	temp;

	height = data->wall_h;
	tmp = floor(data->hit_pos);
	hit_pos2 = data->hit_pos;
	hit_pos2 = hit_pos2 - tmp;
	tmp_h = height / 63;
	if (data->wall.side == 'W' || data->wall.side == 'S')
		hit_pos2 = 1 - hit_pos2;
	tmp_v = hit_pos2 * 63;
	temp = (y - data->wall.top) / tmp_h;
	data->img.addr[y * 4 * 800 + x * 4 + 0] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 0];
	data->img.addr[y * 4 * 800 + x * 4 + 1] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 1];
	data->img.addr[y * 4 * 800 + x * 4 + 2] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 2];
	data->img.addr[y * 4 * 800 + x * 4 + 3] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 3];
	data->i += 4;
	if (!data->text[0]->addr[data->i])
		data->i = 0;
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
		data->img.addr[y * 4 * 800 + x * 4 + 0] = (pixel >> 24);
		data->img.addr[y * 4 * 800 + x * 4 + 1] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 2] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 4] = (pixel) & 0xFF;
	}
	else if (data->img.endian == 0)
	{
		data->img.addr[y * 4 * 800 + x * 4 + 0] = (pixel) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 1] = (pixel >> 8) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 2] = (pixel >> 16) & 0xFF;
		data->img.addr[y * 4 * 800 + x * 4 + 4] = (pixel >> 24);
	}
}

int get_color(t_data *data)
{
	if (data->wall.side == 'W')
		return (0x00FF3333); // west wall - light red
	else if (data->wall.side == 'E')
		return (0x00CC0000); // east wall - dark red
	else if (data->wall.side == 'S')
		return (0xAE3018); // south wall - orange
	else if (data->wall.side == 'N')
		return (0x00FF6666); // north wall - vibrant red
	return (0);
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
	while (i < 600)
	{
		put_pixel(data, ray, i, 0x89CFF3FF); // floor
		i++;
	}
}

void render(t_data *data, int ray) // render the wall
{
	double	top;
	double	bot;

	data->wall_h = ((600 / data->wall.distance) * 1.2) / 
		(cos(data->wall.ray_angle - data->player_pos.angle));
	top = 300 - (data->wall_h / 2); // get the bottom pixel
	bot = 300 + (data->wall_h / 2); // get the top pixel
	data->wall.top = top;
	data->wall.bot = bot;
	if (top < 0)
		top = 0;
	if (bot > 600)
		bot = 600;
	put_floor_and_ceil(data, ray, top, bot);
	put_wall(data, ray, top, bot);
}

