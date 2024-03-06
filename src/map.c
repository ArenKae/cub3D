#include "cub3d.h"

void    print_cpy_map(char **cpy_map)
{
    int i;

    i = 0;
    while (cpy_map[i])
    {
        ft_putstr_fd(cpy_map[i], 1);
        ft_putchar_fd('\n', 1);
        i++;
    }
}

char    **make_cpy_map(t_data *data)
{
    char **cpy_map;
    int i;

    i = 0;
    cpy_map = malloc(sizeof(char *) * (data->map_height + 1));
    while (i < data->map_height)
    {
        cpy_map[i] = malloc(sizeof(char) * (data->map_lenght + 1));
        i++;
    }
    return (cpy_map);
}

void    fill_cpy_map(t_data *data, char **cpy_map)
{
    int x;
    int y;

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_lenght)
        {
            if (data->map[y][x] == ' ')
                cpy_map[y][x] = '1';
            else if (data->map[y][x] != '1' && data->map[y][x] != '0')
                cpy_map[y][x] = '\0';
            else
                cpy_map[y][x] = data->map[y][x];
            x++;
        }
        y++;
    }
    cpy_map[y] = NULL;
}

int	try_move_path(char **map, int x, int y, int i)
{
	if (i == 1)
		if (map[y][x + 1] && map[y][x + 1] == '0')
			return (i);
	if (i == 2)
		if (x > 0 && map[y][x - 1] && map[y][x - 1] == '0')
			return (i);
	if (i == 3)
		if (map[y + 1][x] && map[y + 1][x] == '0')
			return (i);
	if (i == 4)
		if (y > 0 && map[y - 1][x] && map[y - 1][x] == '0')
			return (i);
	return (0);
}

void	make_move_path(char **map, int x, int y, int i)
{
	if (i == 1)
		(map[y][x + 1] = 'A');
	if (i == 2)
		(map[y][x - 1] = 'A');
	if (i == 3)
		(map[y + 1][x] = 'A');
	if (i == 4)
		(map[y - 1][x] = 'A');
}

void    check_is_closed(char **map, int x, int y)
{
    if (y == 0 || !map[y - 1][x])
        printf("error\n");
    else if (!map[y + 1][x])
        printf("error\n");
    else if (x == 0 || !map[y][x - 1])
        printf("error\n");
    else if (!map[y][x + 1])
        printf("error\n");
}

int     unclosed_map(t_data *data, char **map, int x, int y)
{
    if (y == 0 || x == 0)
        return (1);
    if (x == (data->map_lenght - 1) || y == (data->map_height - 1))
        return (1);
    if (!map[y - 1][x])
        return (1);
    else if (!map[y + 1][x])
        return (1);
    else if (!map[y][x - 1])
        return (1);
    else if (!map[y][x + 1])
        return (1);
    return (0);
}

int check_valid_path(t_data *data, char **map, int x, int y)
{
	int	i;

	i = 1;
	while (i < 5)
	{
        if (unclosed_map(data, map, x, y))
        {
            printf("error\n");
            return (0);
        }
		else if (try_move_path(map, x, y, i) > 0)
		{
			make_move_path(map, x, y, i);
			if (i == 1)
				x = x + 1;
			if (i == 2)
				x = x - 1;
			if (i == 3)
				y = y + 1;
			if (i == 4)
				y = y - 1;
			check_valid_path(data, map, x, y);
		}
		i++;
	}
	return (1);
}

int init_check_closed(t_data *data, char **map)
{
    int x;
    int y;

    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '0')
            {
                map[y][x] = 'A';
                if (!check_valid_path(data, map, x, y))
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}

int check_map(t_data *data)
{
    printf("map height : %d\n", data->map_height);
    printf("map len : %d\n", data->map_lenght);
    char **cpy_map;

    cpy_map = make_cpy_map(data);
    fill_cpy_map(data, cpy_map);
    // print_cpy_map(cpy_map);
    if (!init_check_closed(data, cpy_map))
        return (0);
    // print_cpy_map(cpy_map);

    return (1);
}