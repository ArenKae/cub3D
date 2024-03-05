#include "cub3d.h"

int get_map_len(t_data *data, int *height, int *len)
{
    int x;

    while (data->file[*height])
    {
        x = 0;
        while (data->file[*height][x])
            x++;
        if (x > len)
            len = x;
        y++;
    }
}

void    malloc_map(t_data *data, int height, int len)
{
    int i;

    i = 0;
    data->map = malloc(sizeof(char *) * height);
    while (i < height)
    {
        data->map[i] = malloc(sizeof(char) * len + 1);
        i++;
    }
}

void    fill_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (data->file[y])
    {
        x = 0;
        while (data->file[y][x])
        {
            data->map[y][x] = data->file[y][x];
            x++;
        }
        y++;
    }
}

void map_parsing(t_data *data)
{
    int len;
    int height;

    len = 0;
    height = 0;
    get_map_len(data, &height, &len);
    malloc_map(data, height, len);
    fill_map(data);
}

