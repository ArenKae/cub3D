/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:31:23 by acosi             #+#    #+#             */
/*   Updated: 2024/02/05 03:51:18 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>


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

void	get_texture(t_context *context, double graycos, double graysin, double gy, double gx)
{
	double	ray_cos;
	double	ray_sin;

	ray_cos = graycos / 2;
	if (ray_cos < 0)
		ray_cos = -ray_cos;
	ray_sin = graysin / 2;
	if (ray_sin < 0)
		ray_sin = -ray_sin;
	fprintf(stderr, "ray_cos : %lf\n", ray_cos);
	fprintf(stderr, "ray_sin : %lf\n", ray_sin);
	if (context->map[(int)(gy - ray_sin)][(int)gx] != '1')
		fprintf(stderr, "north\n");
	else if (context->map[(int)(gy + ray_sin)][(int)gx] != '1')
		fprintf(stderr, "south\n");
	else if (context->map[(int)gy][(int)(gx + ray_cos)] != '1')
		fprintf(stderr, "east\n");
	else if (context->map[(int)gy][(int)(gx - ray_cos)] != '1')
		fprintf(stderr, "west\n");
}

void get_color(double ray_angle, int flag) // get the color of the wall
{
 if (flag == 0)
 {
  if (ray_angle > (3.141592 / 2) && ray_angle < (3 * 3.141592) / 2)
   fprintf(stderr, "east\n");
  else
   fprintf(stderr, "west\n");
 }
 else
 {
  if (ray_angle > 0 && ray_angle < 3.141592)
   fprintf(stderr, "south\n");
  else
   fprintf(stderr, "north\n");
 }
}

int wall_hit(double x, double y, t_context *context) // check the wall hit
{
 int  x_m;
 int  y_m;

 if (x <= 1 || y <= 1)
  return (0);
 x_m = floor(x);
 y_m = floor(y);
 if ((y_m > 8 || x_m > 8))
  return (0);
 if (context->map[y_m] && x_m <= (int)strlen(context->map[y_m]))
  if (context->map[y_m][x_m] == '1')
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
	if (angle > 3.141592)
  		x_step *= -1;
	if (angle > 0 && angle < 3.141592)
		y_step = -1;
	// printf("h x_step : %lf\n", x_step);
	// printf("h y_step : %lf\n", y_step);
	while (wall_hit(h_x, h_y, context))
	{
		h_x += x_step;
		h_y += y_step;
		printf("h x : %lf\n", h_x);
		printf("h y : %lf\n\n", h_y);
		sleep (1);
	}
	*x_impact = h_x;
	*y_impact = h_y;
	// printf("h x_impact : %lf\n", h_x);
	// printf("h y_impact : %lf\n", h_y);
	return (sqrt(pow(h_x - context->player_pos.x, 2) + pow(h_y - context->player_pos.y, 2)));
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
	if (angle < 4.71239 && angle > 1.5708)
		x_step = -1;
	if (angle > 0 && angle < 3.141592 && y_step > 0)
	{
		y_step *= -1;
	}
	else if (angle > 3.141592 && y_step < 0)
		y_step *= -1;
	// if (angle > 0 && angle < 3.141592)
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
	// ray_angle = context->double_pos.angle - 0.610865;
	ray_angle = context->double_pos.angle;
	if (ray_angle < 0)
		ray_angle = 6.28319 + ray_angle;
	while (ray < 1920)
	{
		flag = 0;
		printf("ray angle : %lf\n", ray_angle * 180 / 3.141592);
		h_inter = get_h_inter(context, ray_angle, &x_impact, &y_impact);
		v_inter = get_v_inter(context, ray_angle, &x_impact, &y_impact);
		ray_angle += 0.000636;
		if (ray_angle > 6.28319)
			ray_angle = 0;
		if (ray_angle < 0)
			ray_angle = 6.28319;
		if (v_inter <= h_inter)
		{
			distance = v_inter;
		}
		else
		{
			flag = 1;
			distance = h_inter;
		}
		printf("ray angle : %lf\n", ray_angle * 180 / 3.141592);
		printf("%d\n", flag);
		get_color(ray_angle, flag);
		printf("distance : %lf\n\n\n\n", distance);
		ray++;
	}
}

int	key_press(int keycode, t_context *context)
{
	if (keycode == 119)
	{
		context->player_pos.x += (sin(context->double_pos.angle) / 2);
		context->player_pos.y += (cos(context->double_pos.angle) / 2);
	}
	if (keycode == 115)
	{
		context->player_pos.x -= (sin(context->double_pos.angle) / 2);
		context->player_pos.y -= (cos(context->double_pos.angle) / 2);
	}
	if (keycode == 100)
	{
		context->player_pos.x += (cos(context->double_pos.angle) / 2);
		context->player_pos.y -= (sin(context->double_pos.angle) / 2);
	}
	if (keycode == 97)
	{
		context->player_pos.x -= (cos(context->double_pos.angle) / 2);
		context->player_pos.y += (sin(context->double_pos.angle) / 2);
	}
	if (keycode == 65363)
	{
		context->double_pos.angle = context->double_pos.angle + (2.5 * 3.141592 / 180);
		if (context->double_pos.angle >= 6.239557)
			context->double_pos.angle = 0;
	}
	if (keycode == 65361)
	{
		context->double_pos.angle = context->double_pos.angle - (2.5 * 3.141592 / 180);
		if (context->double_pos.angle <= 0)
			context->double_pos.angle = 6.239557;
	}
	raycast(context);
	printf("x : %lf\n", context->player_pos.x);
	printf("y : %lf\n", context->player_pos.y);
	printf("angle : %lf\n", context->double_pos.angle * 180 / 3.141592);
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
	context.map = malloc(sizeof(char *) * 10);
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
	context.double_pos.angle = 1 * 3.141592 / 180;
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