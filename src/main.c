/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/02/06 03:49:20 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*window_init(t_context *context)
{
	context->window = mlx_new_window(context->game,
			800, 600, "Cub3d");
	return (context->window);
}

int	destroy_window(t_context *context)
{
	int	i;

	i = 0;
	while (i <= 11)
	{
		mlx_destroy_image(context->game, context->data[i].img_ptr);
		i++;
	}
	mlx_destroy_window(context->game, context->window);

	exit(0);
}

void my_mlx_pixel_put(t_context *context, int x, int y, int color) // put the pixel
{
	if (x < 0) // check the x position
		return ;
	else if (x >= 800)
		return ;
	if (y < 0) // check the y position
		return ;
	else if (y >= 600)
		return ;
	mlx_pixel_put(context->img, context->window, x, y, color); // put the pixel
}

void draw_floor_ceiling(t_context *context, int ray, int t_pix, int b_pix) // draw the floor and the ceiling
{
	int  i;

	i = b_pix;
	while (i < 600)
	{
		my_mlx_pixel_put(context, ray, i, 0xB99470FF); // floor
		i++;
	}
	i = 0;
	while (i < t_pix)
	{
		my_mlx_pixel_put(context, ray, i, 0x89CFF3FF); // ceiling
		i++;
	}
}

int get_color(t_context *context)
{
	if (context->wall.side == 'W')
		return (0xB5B5B5FF); // west wall
	else if (context->wall.side == 'E')
		return (0xB5B5B5FF); // east wall
	else if (context->wall.side == 'S')
		return (0xF5F5F5FF); // south wall
	else if (context->wall.side == 'N')
		return (0xF5F5F5FF); // north wall
	return (0);
}

void draw_wall(t_context *context, int ray, int t_pix, int b_pix) // draw the wall
{
	int color;

	color = get_color(context);
	while (t_pix < b_pix)
	{
		my_mlx_pixel_put(context, ray, t_pix, color);
		t_pix++;
	}
}

void render_wall(t_context *context, int ray) // render the wall
{
	double wall_h;
	double b_pix;
	double t_pix;

	context->wall.distance *= cos(context->wall.ray_angle - context->player_pos.angle); // fix the fisheye
	printf("distance = %lf\n", context->wall.distance);
	wall_h = (1 / context->wall.distance) * ((800/ 2) / tan(75 / 2)); // get the wall height
	b_pix = (600 / 2) + (wall_h / 2); // get the bottom pixel
	t_pix = (600 / 2) - (wall_h / 2); // get the top pixel
	if (b_pix > 600) // check the bottom pixel
		b_pix = 600;
	if (t_pix < 0) // check the top pixel
		t_pix = 0;
	draw_wall(context, ray, t_pix, b_pix); // draw the wall
	// draw_floor_ceiling(context, ray, t_pix, b_pix); // draw the floor and the ceiling
}

void get_wall_side(t_context *context, double ray_angle, int flag) // get the color of the wall
{
	if (flag == 0)
	{
		if (ray_angle > (M_PI / 2) && ray_angle < (3 * M_PI) / 2)
			context->wall.side = 'E';
		else
			context->wall.side = 'W';
	}
	else
	{
		if (ray_angle > 0 && ray_angle < M_PI)
			context->wall.side = 'S';
		else
			context->wall.side = 'N';
	}
}

int wall_hit(double x, double y, t_context *context) // check the wall hit
{
	int  x_map;
	int  y_map;

	if (x <= 1 || y <= 1)
		return (0);
	if (x > 8 || y > 8)
		return (0);
	x_map = floor(x);
	y_map = floor(y);
	if (context->map[y_map] && x_map <= (int)strlen(context->map[y_map]))
		if (context->map[y_map][x_map] == '1')
			return (0);
	return (1);
}

void	get_first_h_inter(t_context *context)
{
	double	x_dif;
	double	y_dif;
	double	x_pos;
	double	y_pos;
	if (context->inter.y_step <= 0)
	{
		y_dif = context->inter.y - floor(context->inter.y);
		y_pos = context->inter.y - y_dif;
	}
	else
	{
		y_dif = ceil(context->inter.y) - context->inter.y;
		y_pos = context->inter.y + y_dif;
	}
	x_dif = context->inter.x_step * y_dif;
	x_pos = context->inter.x + x_dif;
	context->inter.x = x_pos;
	context->inter.y = y_pos;
}


float get_h_inter(t_context *context, double *x_impact, double *y_impact)
{
	context->inter.y_step = 1;
	context->inter.x_step = 1 / tan(context->wall.ray_angle);
	context->inter.x = context->player_pos.x;
	context->inter.y = context->player_pos.y;
	if (context->wall.ray_angle > M_PI)
  		context->inter.x_step *= -1;
	if (context->wall.ray_angle > 0 && context->wall.ray_angle < M_PI)
		context->inter.y_step = -1;
	get_first_h_inter(context);
	while (wall_hit(context->inter.x, context->inter.y, context))
	{
		context->inter.x += context->inter.x_step;
		context->inter.y += context->inter.y_step;
	}
	*x_impact = context->inter.x;
	*y_impact = context->inter.y;
	return (sqrt(pow(context->inter.x - context->player_pos.x, 2) + pow(context->inter.y - context->player_pos.y, 2)));
}

void	get_first_v_inter(t_context *context)
{
	double	x_dif;
	double	y_dif;
	double	x_pos;
	double	y_pos;
	if (context->inter.x_step < 0)
	{
		x_dif = context->inter.x - floor(context->inter.x);
		x_pos = context->inter.x - x_dif;
	}
	else
	{
		x_dif = ceil(context->inter.x) - context->inter.x;
		x_pos = context->inter.x + x_dif;
	}
	y_dif = context->inter.y_step * x_dif;
	y_pos = context->inter.y + y_dif;
	context->inter.x = x_pos;
	context->inter.y = y_pos;
}

float get_v_inter(t_context *context, double *x_impact, double *y_impact)
{
	context->inter.x_step = 1; 
	context->inter.y_step = 1 * tan(context->wall.ray_angle);
	context->inter.x = context->player_pos.x;
	context->inter.y = context->player_pos.y;
	if (context->wall.ray_angle < (M_PI * 3 / 2) && context->wall.ray_angle > (M_PI / 2))
		context->inter.x_step = -1;
	if ((context->wall.ray_angle > 0 && context->wall.ray_angle < M_PI && context->inter.y_step > 0) || ((context->wall.ray_angle > M_PI && context->inter.y_step < 0)))
	{
		context->inter.y_step *= -1;
	}
	get_first_v_inter(context);
	while (wall_hit(context->inter.x, context->inter.y, context))
	{
		context->inter.x += context->inter.x_step;
		context->inter.y += context->inter.y_step;
	}
	*x_impact = context->inter.x;
	*y_impact = context->inter.y;
	return (sqrt(pow(context->inter.x - context->player_pos.x, 2) + pow(context->inter.y - context->player_pos.y, 2)));
}


void	raycast(t_context *context)
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
	context->wall.ray_angle = context->player_pos.angle - 0.523599;
	if (context->wall.ray_angle < 0)
		context->wall.ray_angle = M_PI * 2 + context->wall.ray_angle;
	while (ray < 801)
	{
		if (context->wall.ray_angle >= M_PI * 2)
			context->wall.ray_angle = 0;
		flag = 0;
		if (context->wall.ray_angle == 0)
			context->wall.ray_angle = 0.000001;
		h_inter = get_h_inter(context, &x_impact, &y_impact);
		v_inter = get_v_inter(context, &x_impact, &y_impact);
		context->wall.ray_angle += 0.001309;
		if (v_inter <= h_inter)
			context->wall.distance = v_inter;
		else
		{
			flag = 1;
			context->wall.distance = h_inter;
		}
		ray++;
	}
}

int	key_press(int keycode, t_context *context)
{
	if (keycode == 119)
	{
		context->player_pos.x += (cos(context->player_pos.angle) / 5);
		context->player_pos.y -= (sin(context->player_pos.angle) / 5);
	}
	if (keycode == 115)
	{
		context->player_pos.x -= (cos(context->player_pos.angle) / 5);
		context->player_pos.y += (sin(context->player_pos.angle) / 5);
	}
	if (keycode == 100)
	{
		context->player_pos.x += (sin(context->player_pos.angle) / 5);
		context->player_pos.y += (cos(context->player_pos.angle) / 5);
	}
	if (keycode == 97)
	{
		context->player_pos.x -= (sin(context->player_pos.angle) / 5);
		context->player_pos.y -= (cos(context->player_pos.angle) / 5);
	}
	if (keycode == 65363)
	{
		context->player_pos.angle = context->player_pos.angle - (2.5 * M_PI / 180);
		if (context->player_pos.angle >= M_PI * 2)
			context->player_pos.angle = 0;
	}
	if (keycode == 65361)
	{
		context->player_pos.angle = context->player_pos.angle + (2.5 * M_PI / 180);
		if (context->player_pos.angle <= 0)
			context->player_pos.angle = M_PI * 2;
	}
	if (context->player_pos.angle > M_PI * 2)
		context->player_pos.angle = 2.5 * M_PI / 180;
	if (context->player_pos.angle < 2.4 * M_PI / 180)
		context->player_pos.angle = M_PI * 2;
	raycast(context);
	return (0);
}

void	hooks_handler(t_context *context)
{
	mlx_hook(context->window, KeyPress, KeyPressMask, key_press, context);
}


int	main(int ac, char **av)
{
	(void)av;
	t_context	context;
	context.map = malloc(sizeof(char *) * 9);
	context.map[0] = strdup("11111111");
 	context.map[1] = strdup("10000001");
 	context.map[2] = strdup("10000001");
 	context.map[3] = strdup("10000001");
 	context.map[4] = strdup("10000001");
 	context.map[5] = strdup("10000001");
 	context.map[6] = strdup("10000001");
 	context.map[7] = strdup("10000001");
 	context.map[8] = strdup("11111111");

	context.player_pos.x = 4;
	context.player_pos.y = 4;
	context.player_pos.angle = 29 * M_PI / 180;
	context.value = 0;
	context.frames = 0;
	if (ac == 2)
	{
		context.game = mlx_init();
		if (!context.game)
			return (1);
		window_init(&context);
		context.img = mlx_new_image(context.game, 800, 600);
		// put_sprites(&context);
		// mlx_hook(context.window, DestroyNotify, KeyReleaseMask,
		// 	destroy_window, &context);
		hooks_handler(&context);
		//mlx_loop_hook(context.game, raycast, &context);
		// mlx_key_hook(context.window, on_key, &context);
		// mlx_loop_hook(context.game, init_patrol, &context);
		mlx_loop(context.game);
	}
	return (0);
}