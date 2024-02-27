/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:00:42 by acosi             #+#    #+#             */
/*   Updated: 2024/02/27 22:41:06 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= 800)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= 600)
		return ;
	//mlx_pixel_put(data->mlx, data->win, x, y, color); // put the pixel
	data->img.addr[y * 800 + x] = color;
}

void draw_floor_ceiling(t_data *data, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
	int  i;

	i = b_pix;
	while (i < 600)
	{
		my_mlx_pixel_put(data, ray, i, 0); // floor
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		my_mlx_pixel_put(data, ray, i, 0x89CFF3FF); // ceiling
		i++;
	}
}

int get_color(t_data *data)
{
	if (data->wall.side == 'W')
		return (0x00FF3333); // west wall
	else if (data->wall.side == 'E')
		return (0x00CC0000); // east wall
	else if (data->wall.side == 'S')
		return (0x00FF0000); // south wall
	else if (data->wall.side == 'N')
		return (0x00FF6666); // north wall
	return (0);
}

void draw_wall(t_data *data, int ray, int t_pix, int b_pix) // draw the wall
{
	int color;

	(void)ray;
	color = get_color(data);
	while (t_pix >b_pix)
	{
		my_mlx_pixel_put(data, ray, t_pix, color);
		t_pix--;
	}
	//printf(">>tpix = %d, bpix = %d\n", t_pix, b_pix);
}

void render_wall(t_data *data, int ray) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	data->wall.distance *= cos(data->wall.ray_angle - data->player_pos.angle); // fix the fisheye
	//printf("distance = %lf\n", data->wall.distance);
	wall_h = (1 / data->wall.distance) * ((800/ 2) / tan(75 / 2)); // get the wall height
	b_pix = (600 / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (600 / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > 600) // check the bottom pixel
		b_pix = 600;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_floor_ceiling(data, ray, t_pix, b_pix); // draw the floor and the ceiling
	draw_wall(data, ray, t_pix, b_pix); // draw the wall
}

