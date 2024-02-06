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
			400, 400, "Cub3d");
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

void get_wall_side(double ray_angle, int flag) // get the color of the wall
{
 if (flag == 0)
 {
  if (ray_angle > (M_PI / 2) && ray_angle < (3 * M_PI) / 2)
   fprintf(stderr, "east\n");
  else
   fprintf(stderr, "west\n");
 }
 else
 {
  if (ray_angle > 0 && ray_angle < M_PI)
   fprintf(stderr, "south\n");
  else
   fprintf(stderr, "north\n");
 }
}

int wall_hit(double x, double y, t_context *context) // check the wall hit
{
 int  x_map;
 int  y_map;

 if (x <= 1 || y <= 1)
  return (0);
 x_map = floor(x);
 y_map = floor(y);
 if ((y_map > 8 || x_map > 8))
  return (0);
 if (context->map[y_map] && x_map <= (int)strlen(context->map[y_map]))
  if (context->map[y_map][x_map] == '1')
   return (0);
 return (1);
}

float get_h_inter(t_context *context, double angle, double *x_impact, double *y_impact)
{
	double h_x;
	double h_y;
	double x_step;
	double y_step;

	y_step = 1;
	x_step = 1 / tan(angle);
	h_x = context->player_pos.x;
	h_y = context->player_pos.y;
	if (angle > M_PI)
  		x_step *= -1;
	if (angle > 0 && angle < M_PI)
		y_step = -1;
	// printf("h x_step : %lf\n", x_step);
	// printf("h y_step : %lf\n", y_step);
	while (wall_hit(h_x, h_y, context))
	{
		h_x += x_step;
		h_y += y_step;
		// printf("h x : %lf\n", h_x);
		// printf("h y : %lf\n\n", h_y);
		// sleep (1);
	}
	*x_impact = h_x;
	*y_impact = h_y;
	// printf("h x_impact : %lf\n", h_x);
	// printf("h y_impact : %lf\n", h_y);
	return (sqrt(pow(h_x - context->player_pos.x, 2) + pow(h_y - context->player_pos.y, 2)));
}

void	get_first_v_inter(double v_x, double v_y, double x_step, double y_step, double angle)
{
	(void)y_step;
	(void)v_y;
	double	x_dif;
	double	y_dif;
	double	x_pos;
	double	y_pos;
	(void)angle;
	printf("x step = %lf\n", x_step);
	printf("y step = %lf\n", y_step);
	if (x_step <= 0)
	{
		printf("1\n");
		x_dif = v_x - floor(v_x);
		x_pos = v_x - x_dif;
	}
	else
	{
		printf("0\n");
		x_dif = ceil(v_x) - v_x;
		x_pos = v_x + x_dif;
	}
	// y_dif = x_dif * tan(angle);
	y_dif = y_step * x_dif;
	y_pos = v_y + y_dif;
	printf("x_dif = %lf\n", x_dif);
	printf("y_dif = %lf\n", y_dif);
	printf("x inter pos = %lf\n", x_pos);
	printf("y inter pos = %lf\n", y_pos);
}

float get_v_inter(t_context *context, double angle, double *x_impact, double *y_impact)
{
	double v_x;
	double v_y;
	double x_step;
	double y_step;

	x_step = 1; 
	y_step = 1 * tan(angle);
	v_x = context->player_pos.x;
	v_y = context->player_pos.y;
	if (angle < (M_PI * 3 / 2) && angle > (M_PI / 2))
		x_step = -1;
	if ((angle > 0 && angle < M_PI && y_step > 0) || ((angle > M_PI && y_step < 0)))
	{
		y_step *= -1;
	}
	get_first_v_inter(v_x, v_y, x_step, y_step, angle);
	// else if (angle > M_PI && y_step < 0)
	// 	y_step *= -1;
	// if (angle > 0 && angle < M_PI)
	// 	y_step *= -1;
	// printf("v x_step : %lf\n", x_step);
	// printf("v y_step : %lf\n", y_step);
	while (wall_hit(v_x, v_y, context))
	{
		v_x += x_step;
		v_y += y_step;
		printf("v x : %lf\n", v_x);
		printf("v y : %lf\n\n", v_y);
		sleep (1);
	}
	*x_impact = v_x;
	*y_impact = v_y;
	// printf("v x_impact : %lf\n", v_x);
	// printf("v y_impact : %lf\n", v_y);
	return (sqrt(pow(v_x - context->player_pos.x, 2) + pow(v_y - context->player_pos.y, 2)));
}


void	raycast(t_context *context)
{
	double	h_inter;
	double	v_inter;
	int		ray;
	double	ray_angle;
	double	distance;
	int		flag;
	double	x_impact;
	double	y_impact;

	ray = 0;
	flag = 0;
	(void)flag;
	(void)distance;
	// ray_angle = context->double_pos.angle - 0.610865;
	ray_angle = context->double_pos.angle;
	if (ray_angle > M_PI * 2)
		ray_angle = 0 + ray_angle;
	while (ray < 2)
	{
		flag = 0;
		// printf("ray angle : %lf\n", ray_angle * 180 / M_PI);
		h_inter = get_h_inter(context, ray_angle, &x_impact, &y_impact);
		v_inter = get_v_inter(context, ray_angle, &x_impact, &y_impact);
		ray_angle += 0.000636;
		if (ray_angle > M_PI)
			ray_angle = 0;
		if (ray_angle < 0)
			ray_angle = M_PI;
		if (v_inter <= h_inter)
		{
			distance = v_inter;
		}
		else
		{
			flag = 1;
			distance = h_inter;
		}
		// printf("ray angle : %lf\n", ray_angle * 180 / M_PI);
		// printf("%d\n", flag);
		// get_wall_side(ray_angle, flag);
		// printf("distance : %lf\n\n\n\n", distance);
		// sleep(1);
		ray++;
	}
}

int	key_press(int keycode, t_context *context)
{
	if (keycode == 119)
	{
		if (context->double_pos.angle < (M_PI * 2 / 3) && context->double_pos.angle > (M_PI / 2))
			context->player_pos.x -= (sin(context->double_pos.angle) / 5);
		else
			context->player_pos.x += (sin(context->double_pos.angle) / 5);
		if (context->double_pos.angle <= M_PI)
			context->player_pos.y -= (cos(context->double_pos.angle) / 5);
		else
			context->player_pos.y += (cos(context->double_pos.angle) / 5);
	}
	if (keycode == 115)
	{
		if (context->double_pos.angle < (M_PI * 2 / 3) && context->double_pos.angle > (M_PI / 2))
			context->player_pos.x += (sin(context->double_pos.angle) / 5);
		else
			context->player_pos.x -= (sin(context->double_pos.angle) / 5);
		if (context->double_pos.angle <= M_PI)
			context->player_pos.y += (cos(context->double_pos.angle) / 5);
		else
			context->player_pos.y -= (cos(context->double_pos.angle) / 5);
	}
	if (keycode == 100)
	{
		context->player_pos.x += (cos(context->double_pos.angle) / 5);
		context->player_pos.y -= (sin(context->double_pos.angle) / 5);
	}
	if (keycode == 97)
	{
		context->player_pos.x -= (cos(context->double_pos.angle) / 5);
		context->player_pos.y += (sin(context->double_pos.angle) / 5);
	}
	if (keycode == 65363)
	{
		context->double_pos.angle = context->double_pos.angle + (2.5 * M_PI / 180);
		if (context->double_pos.angle >= M_PI * 2)
			context->double_pos.angle = 0;
	}
	if (keycode == 65361)
	{
		context->double_pos.angle = context->double_pos.angle - (2.5 * M_PI / 180);
		if (context->double_pos.angle <= 0)
			context->double_pos.angle = M_PI * 2;
	}
	raycast(context);
	printf("x : %lf\n", context->player_pos.x);
	printf("y : %lf\n", context->player_pos.y);
	printf("angle : %lf\n\n\n", context->double_pos.angle * 180 / M_PI);
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
	// printf("player x : %d\n", context.player_pos.x);
	// printf("player y : %d\n", context.player_pos.y);
	context.double_pos.angle = 45 * M_PI / 180;
	context.value = 0;
	context.frames = 0;
	if (ac == 2)
	{
		context.game = mlx_init();
		if (!context.game)
			return (1);
		window_init(&context);
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