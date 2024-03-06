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

int check_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x])
        {
            if (data->map[y][x] == '0')
                if (unclosed_map(data, data->map, x, y))
                    return (0);
            x++;
        }
        y++;
    }
    return (1);
}

int check_map_init(t_data *data)
{
    if (data->parse.pos_flag != 1)
    {
        printf("error\n");
        return (0);
    }
    if (check_map(data))
        return (1);
    printf("map error\n");
    return (0);
}