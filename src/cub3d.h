/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:53 by acosi             #+#    #+#             */
/*   Updated: 2024/03/05 23:24:02 by acosi            ###   ########.fr       */
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
# include "./libft/get_next_line.h"

/* ---------------------------------------------------------------------------*
							MACROS
 --------------------------------------------------------------------------- */

# define BUFF_SIZE 512
# define WIN_H 600
# define WIN_L 800
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define RED "\e[31m"

enum	textures_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};

enum	error_msg
{
	INVALID_NAME = 0,
	INVALID_FILE = 1,
	INVALID_TEXTURES = 2,
	INVALID_COLORS = 3,
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

typedef struct s_info
{
	char	*NO;
	char	*SO;
	char	*EA;
	char	*WE;
	char	*F;
	char	*C;
	int		F_hex;
	int		C_hex;
}	t_info;

typedef	struct s_file
{
	char			*line;
	struct s_file	*next;
}		t_file;


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
	double	wall_h;
	double	hit_pos;
	int		move;
	int		rotate;
	int		map_height;
	int		map_lenght;
	int		clock;
	t_pos	player_pos;
	t_file	*file;
	t_wall	wall;
	t_inter	inter;
	t_img	**text;
	t_img	img;
	t_info	fileinfo;
}		t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/*	Parsing & Map checking	*/
int		check_map_name(char *filename);
void	init_map(t_data *data, char *filename);
int		check_map_name(char *s1);

/*	Raycasting	*/
void	raycast(t_data *data);
int	game(t_data *data);

/*	Rendering	*/
void 	render(t_data *data, int ray);

/*	Textures	*/
void	render_texture(t_data *data);

/*	Utils	*/ 
int		rgb_to_hexa(int *color, int r, int g, int b);
void	exit_error(char *msg, int status);
int		destroy_window(t_data *data);
void	print_error(int msg);
int		char_isdigit(char c);

#endif
