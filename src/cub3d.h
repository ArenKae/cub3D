/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acosi <acosi@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:30:53 by acosi             #+#    #+#             */
/*   Updated: 2023/09/22 17:35:37 by acosi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define BUFF_SIZE 512
# define SQUARE_SIZE 50

# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_data
{
	int		*addr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		img_width;
	int		img_height;	
}		t_data;

typedef struct s_pos
{
	double	x;
	double  y;
	double x2;
	double	y2;
}		t_pos;

typedef	struct s_double
{
	double	x;
	double	y;
	double	angle;
}		t_double;

typedef struct s_patrol
{
	t_pos			pat_pos;
	struct s_patrol	*next;
}			t_patrol;

typedef struct s_context
{
	void	*window;
	void	*game;
	char	**map;
	char	*str;
	int		window_x;
	int		window_y;
	int		value;
	int		frames;
	t_pos	player_pos;
	t_double	double_pos;
	t_data	data[13];
}		t_context;

typedef struct s_read
{
	int				ret;
	char			buf[BUFF_SIZE];
	struct s_read	*next;
}		t_read;


#endif
