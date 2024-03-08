/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:53 by acosi             #+#    #+#             */
/*   Updated: 2024/03/08 13:30:21 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"

/* -----------------------------------------------------------------*
							MACROS
 ----------------------------------------------------------------- */

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# define RED "\e[31m"
# define STOP "\e[0m"

enum	e_textures_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
};

enum	e_error_msg
{
	INVALID_NAME = 0,
	INVALID_FILE = 1,
	INVALID_TEXTURES = 2,
	INVALID_COLORS = 3,
	INVALID_MAP = 4,
	OPEN_ERROR = 5,
};

/* -----------------------------------------------------------------*
							STRUCTURES
 ----------------------------------------------------------------- */

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

typedef struct s_pos
{
	double	x;
	double	y;
	double	angle;
}		t_pos;

typedef struct s_wall
{
	char	side;
	double	distance;
	double	ray_angle;
	int		top;
	int		bot;
}			t_wall;

typedef struct s_inter
{
	double	x;
	double	y;
	double	x_step;
	double	y_step;
}			t_inter;

typedef struct s_info
{
	char	*no;
	char	*so;
	char	*ea;
	char	*we;
	char	*f;
	char	*c;
	int		f_hex;
	int		c_hex;
	int		n;
	int		s;
	int		e;
	int		w;
}	t_info;

typedef struct s_file
{
	char			*line;
	struct s_file	*next;
}		t_file;

typedef struct s_parse
{
	int		map_flag;
	int		pos_flag;
	int		n;
	int		s;
	int		e;
	int		w;
	int		f;
	int		c;
}		t_parse;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	char	*str;
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

/* -----------------------------------------------------------------*
							FUNCTIONS
 ----------------------------------------------------------------- */

/*	Parsing & Map checking	*/
int		check_map_name(t_data *data, char *filename);
int		check_map_init(t_data *data);
void	init_map(t_data *data, char *filename);
void	fill_map(t_data *data);
void	get_player_pos(t_data *data, int y, int x);
void	get_map_size(t_data *data);
void	convert_colors(t_data *data);
void	store_info(t_data *data, char *line);

/*	File checking	*/
int		missing_info(t_data *data);
int		multiple_infos(t_data *data);
void	get_format_path(char *path, char *side, int *malloc);
int		check_comma(char *str);
int		check_rgb(char **rgb);

/*	Movement	*/
void	player_movement(t_data *data);
void	player_rotation(t_data *data);
float	get_h_inter(t_data *data, double *x_impact);
float	get_v_inter(t_data *data, double *y_impact);

/*	Raycasting	*/
void	raycast_init(t_data *data);
int		game(t_data *data);

/*	Rendering	*/
void	render(t_data *data, int ray);

/*	Textures	*/
void	render_texture(t_data *data);

/*	Keys and hook	*/
void	hooks_handler(t_data *data);

/*	Utils & error management	*/
int		rgb_to_hexa(int *color, int r, int g, int b);
int		char_isdigit(char c);
char	*trim_spaces(const char *line);
void	get_player_pos(t_data *data, int y, int x);
void	exit_error(char *msg, int status);
void	print_error(t_data *data, int msg);
int		unamed_cub(char *str);

/*	Memory management	*/
void	free_tab(char **tab);
void	free_all(t_data *data);
void	free_tab_error(t_data *data, char **F, char **C);
void	free_mlx(t_data *data);
void	free_list(t_data *data);
void	free_and_error(t_data *data, char *s1, char *s2);
int		destroy_window(t_data *data);

#endif
