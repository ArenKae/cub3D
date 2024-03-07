/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:53 by acosi             #+#    #+#             */
/*   Updated: 2024/03/07 04:03:10 by acosi            ###   ########.fr       */
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
#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

# define RED "\e[31m"
# define STOP "\e[0m"

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
	INVALID_MAP = 4,
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
	int		N;
	int		S;
	int		E;
	int		W;
}	t_info;

typedef	struct s_file
{
	char			*line;
	struct s_file	*next;
}		t_file;

typedef	struct	s_parse
{
	int	map_flag;
	int	pos_flag;
	int		N;
	int		S;
	int		E;
	int		W;
	int		F;
	int		C;
}		t_parse;

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
	t_img	*text;
	t_img	img;
	t_parse	parse;
	t_info	fileinfo;
}		t_data;

/* ---------------------------------------------------------------------------*
							FUNCTIONS
 --------------------------------------------------------------------------- */

/*	Parsing & Map checking	*/
int		check_map_name(t_data *data, char *filename);
int		check_map_init(t_data *data);
void	init_map(t_data *data, char *filename);

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
void	print_error(t_data * data, int msg);
int		char_isdigit(char c);
void	free_tab(char **tab);
void 	free_all(t_data *data);
void	free_and_error(t_data *data, char **F, char **C);
void	free_mlx(t_data *data);

#endif
