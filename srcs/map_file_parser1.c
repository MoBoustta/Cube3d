/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file_parser1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 18:29:13 by moboustt          #+#    #+#             */
/*   Updated: 2020/10/18 12:20:20 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

int count_lines(const char *buff)
{
    int i;
    int num_lines;

    i = 0;
    num_lines = 0;
    while (buff[i])
    {
        if (buff[i] == '\n')
            num_lines += 1;
        i++;
    }
    return (num_lines);
}

int line_length(const char *line)
{
    int i;

    i = 0;
    while (line[i] != '\0' && line[i] != '\n')
        i++;
    return (i);
}

int fill_out_map(t_struct *data, char *buff)
{
    int i;
    int j;

    i = -1;
    data->count_spt = 0;
    data->n_lines = count_lines(&buff[data->pos]);
    g_lines_length = (int *)malloc((data->n_lines + 1) * sizeof(int));
    data->map = (char **)malloc((data->n_lines + 1) * sizeof(char *));
    while (buff[data->pos] != '\0' && i++ < data->n_lines)
    {
        data->l_length = line_length(&buff[data->pos]);
        g_lines_length[i] = data->l_length;
        data->map[i] = (char *)malloc(sizeof(char) * data->l_length);
        buff[data->pos] == '\n' ? (data->pos += 1) : data->pos;
        j = 0;
        while (j < data->l_length && buff[data->pos] != '\n')
        {
            if (is_not_valid_element(data, buff))
                return (1);
            if (is_player(data, buff))
            {
                data->i = i;
                data->j = j;
                data->map[i][j++] = data->orientation = (unsigned char)buff[data->pos];
                init_player(data);
                data->pos += 1;
                continue;
            }
            data->map[i][j] = buff[data->pos];
            if (is_sprite(data->map[i][j]))
                data->count_spt++;
            data->pos += 1;
            j++;
        }
        data->pos += 1;
    }
    return (TRUE);
}

void initialize_file_struct(t_struct *data)
{
    data->pos = 0;
    data->get_to_map = 0;
    data->width = 0;
    data->height = 0;
    data->f_red = 0;
    data->f_green = 0;
    data->f_blue = 0;
    data->c_red = 0;
    data->c_green = 0;
    data->c_blue = 0;
    data->map = malloc(sizeof(int) * 30);
    ft_memset(data->no, 0, 25);
    ft_memset(data->so, 0, 25);
    ft_memset(data->ea, 0, 25);
    ft_memset(data->we, 0, 25);
    ft_memset(data->sp, 0, 25);
}
