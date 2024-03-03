/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:53 by acosi             #+#    #+#             */
/*   Updated: 2024/03/03 22:04:55 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "./libft/libft.h"

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# define BUFF_SIZE 512
# define SQUARE_SIZE 50
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

enum	textures_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};

/* ---------------------------------------------------------------------------*
							STRUCTURES
 --------------------------------------------------------------------------- */

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		pixel_bits;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef	struct s_pos
{
	double	x;
	double	y;
	double	angle;
}		t_pos;

typedef	struct s_wall
{
	char	side;
	double	distance;
	double	ray_angle;
	int	top;
	int	bot;
}			t_wall;

typedef struct s_inter
{
	double x;
	double y;
	double x_step;
	double y_step;
}			t_inter;

typedef struct s_read
{
	int				ret;
	char			buf[BUFF_SIZE];
	struct s_read	*next;
}		t_read;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*str;
	int		window_x;
	int		window_y;
	int		value;
	int		frames;
	int		i;
	double	wall_h;
	double	hit_pos;
	t_pos	player_pos;
	t_wall	wall;
	t_inter	inter;
	t_img	**text;
	t_img	img;
}		t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/*	Raycasting	*/
void	raycast(t_data *data);

/*	Rendering	*/
void 	render(t_data *data, int ray);

/*	Textures	*/
void	render_texture(t_data *data);

/*	Utils	*/ 
void	exit_error(char *msg, int status);
int		destroy_window(t_data *data);

#endif
