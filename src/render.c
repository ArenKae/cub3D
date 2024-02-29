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

void wall_pixel_put(t_data *data, int x, int y)
{
	int tmp;
	double	height;
	double	tmp_h;
	int	tmp_v;
	int	temp;

	height = data->wall_h * - 1;
	tmp = floor(data->hit_pos);
	data->hit_pos = data->hit_pos - tmp;
	tmp_h = height / 63;
	tmp_v = data->hit_pos * 63;
	// printf("data->hit_pos = %d\n", tmp_v);
	// printf("y = %d\n", y);
	// printf("height = %d\n", height);
	temp = (y - data->wall.t_pix) / tmp_h;
	// printf("height = %lf\n", height);
	// printf("tmp_h = %lf\n", tmp_h);
	// printf("temp = %d\n", temp);
	// printf("tmp_v = %d\n", tmp_v);
	data->img.addr[y * 4 * 800 + x * 4 + 0] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 0];
	data->img.addr[y * 4 * 800 + x * 4 + 1] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 1];
	data->img.addr[y * 4 * 800 + x * 4 + 2] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 2];
	data->img.addr[y * 4 * 800 + x * 4 + 3] = data->text[0]->addr[temp * 4 * 63 + tmp_v * 4 + 3];
	data->i += 4;
	if (!data->text[0]->addr[data->i])
		data->i = 0;
}

void pixel_put(t_data *data, int x, int y, int pixel) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= 800)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= 600)
		return ;
	//mlx_pixel_put(data->mlx, data->win, x, y, pixel); // put the pixel
	if (pixel == -1)
	{
		wall_pixel_put(data, x, y);
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

void draw_wall(t_data *data, int ray, int t_pix, int b_pix) // draw the wall
{
	int pixel;

	(void)pixel;
	//pixel = get_color(data);
	while (t_pix < b_pix)
	{
		pixel_put(data, ray, t_pix, -1);
		t_pix++;
	}
	//printf(">>tpix = %d, bpix = %d\n", t_pix, b_pix);
}

void draw_floor_ceiling(t_data *data, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
	int  i;

	i = t_pix;
	while (i < 600)
	{
		pixel_put(data, ray, i, 0xB99470FF); // floor
		i++;
	}
	i = 0;
	while (i < b_pix)
	{
		pixel_put(data, ray, i, 0x89CFF3FF); // ceiling
		i++;
	}
}

void render(t_data *data, int ray) // render the wall
{
	(void)ray;
	double b_pix;
	double t_pix;

	data->wall.distance *= cos(data->wall.ray_angle - data->player_pos.angle); // fix the fisheye
	//printf("distance = %lf\n", data->wall.distance);
	data->wall_h = (1 / data->wall.distance) * ((800/ 2) / tan(75 / 2)); // get the wall height
	t_pix = (600 / 2) + (data->wall_h / 2); // get the bottom pixel
	b_pix = (600 / 2) - (data->wall_h / 2); // get the top pixel
	data->wall.t_pix = t_pix;
	data->wall.b_pix = b_pix;
	//printf("t_pix = %d\n", data->wall.t_pix);
	//printf("b_pix = %d\n", data->wall.b_pix);
	if (b_pix > 600) // check the bottom pixel
		b_pix = 600;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	// printf("t_pix = %lf\n", t_pix);
	// printf("b_pix = %lf\n", b_pix);
	draw_floor_ceiling(data, ray, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(data, ray, t_pix, b_pix); // draw the wall
}

