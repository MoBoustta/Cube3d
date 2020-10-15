/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:54:01 by moboustt          #+#    #+#             */
/*   Updated: 2020/02/15 14:54:05 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cube3d.h"

void	texture_from_file(t_struct *data)
{
	int		w;
	int		h;

	data->xpm_ptr1 = mlx_xpm_file_to_image(data->mlx_ptr, data->no, &w, &h);
	data->xpm_ptr2 = mlx_xpm_file_to_image(data->mlx_ptr, data->so, &w, &h);
	data->xpm_ptr3 = mlx_xpm_file_to_image(data->mlx_ptr, data->we, &w, &h);
	data->xpm_ptr4 = mlx_xpm_file_to_image(data->mlx_ptr, data->ea, &w, &h);
	data->sprite_xpm = mlx_xpm_file_to_image(data->mlx_ptr, data->sp, &w, &h);
	if (!data->xpm_ptr1 || !data->xpm_ptr2
	|| !data->xpm_ptr3 || !data->xpm_ptr4)
	{
		write(1, "Error : wrong texture path!\n", 28);
		(ft_close(data));
	}
	data->img_data_texture1 = (int *)mlx_get_data_addr(data->xpm_ptr1,
	&data->bpp_text, &data->size_line_text, &data->endian_text);
	data->img_data_texture2 = (int *)mlx_get_data_addr(data->xpm_ptr2,
	&data->bpp_text, &data->size_line_text, &data->endian_text);
	data->img_data_texture3 = (int *)mlx_get_data_addr(data->xpm_ptr3,
	&data->bpp_text, &data->size_line_text, &data->endian_text);
	data->img_data_texture4 = (int *)mlx_get_data_addr(data->xpm_ptr4,
	&data->bpp_text, &data->size_line_text, &data->endian_text);
	data->img_data_texture_sprite = (int *)mlx_get_data_addr(data->sprite_xpm,
	&data->bpp_text, &data->size_line_text, &data->endian_text);
}

void	calculate_wall_projection(t_struct *data)
{
	data->corrected_dsitance = g_rays[data->i_wall_index].distance *
	cos(g_rays[data->i_wall_index].ray_angle - data->rotation_angle);
	data->distance_to_projection_plane = (data->w_width * 0.5)
	/ tan(FOV_ANGLE / 2);
	data->wall_height = (SQUARE_SIZE / data->corrected_dsitance) *
	data->distance_to_projection_plane;
	data->top_pixel = (data->w_height / 2) - (data->wall_height / 2);
	data->top_pixel = data->top_pixel < 0 ? 0 : data->top_pixel;
	data->bottom_pixel = (data->w_height / 2) + (data->wall_height / 2);
	data->bottom_pixel = data->bottom_pixel > data->w_height
	? data->w_height
	: data->bottom_pixel;
}

void	ft_ljodran(t_struct *data, int y)
{
	int *which_text;
	int index;

	data->txt_offset_y = (y + (int)(data->wall_height / 2)
	- (data->w_height / 2)) * ((float)TEX_WIDTH
	/ (int)data->wall_height);
	if (!g_rays[data->i_wall_index].was_hit_vertical
	&& g_rays[data->i_wall_index].is_ray_facing_down)
		which_text = data->img_data_texture1;
	else if (!g_rays[data->i_wall_index].was_hit_vertical
	&& g_rays[data->i_wall_index].is_ray_facing_up)
		which_text = data->img_data_texture2;
	else if ((g_rays[data->i_wall_index].was_hit_vertical)
	&& g_rays[data->i_wall_index].is_ray_facing_left)
		which_text = data->img_data_texture3;
	else if ((g_rays[data->i_wall_index].was_hit_vertical)
	&& g_rays[data->i_wall_index].is_ray_facing_right)
		which_text = data->img_data_texture4;
	index = ((TEX_WIDTH * data->txt_offset_y)
	+ data->txt_offset_x)
	>= (TEX_HEIGHT * TEX_WIDTH)
	? (TEX_WIDTH * TEX_HEIGHT - 1)
	: ((TEX_WIDTH * data->txt_offset_y) + data->txt_offset_x);
	index = index <= 0 ? 0 : index;
	ft_draw(data, data->i_wall_index, y, data->t ? (int)which_text[index] : 0xffffff);
}


void	render_walls(t_struct *data)
{
	int		ceilling;
	int		floor;
	float	y;

	data->i_wall_index = 0;
	texture_from_file(data);
	while (data->i_wall_index++ < data->w_width - 1)
	{
		ceilling = 0;
		calculate_wall_projection(data);
		y = data->top_pixel;
		data->txt_offset_x = (g_rays[data->i_wall_index].was_hit_vertical)
		? ((int)g_rays[data->i_wall_index].wall_h_y % SQUARE_SIZE)
		: ((int)g_rays[data->i_wall_index].wall_h_x % SQUARE_SIZE);
		while (ceilling++ < data->top_pixel)
			ft_draw(data, data->i_wall_index, ceilling,
			creatergb(data->c_red, data->c_green, data->c_blue));
		while (y++ < data->bottom_pixel - 1)
			ft_ljodran(data, y);
		floor = data->bottom_pixel;
		while (floor++ < data->w_height - 1)
			ft_draw(data, data->i_wall_index, floor, creatergb(data->f_red, data->c_green, data->c_blue));
	}
	set_up_sprite(data);
}

void	cast_rays(t_struct *data)
{
	int		ray_id;
	int		i;
	float	ray_angle;

	ray_id = 0;
	i = 0;
	ray_angle = data->rotation_angle - (FOV_ANGLE / 2);
	while (i < data->w_width)
	{
		cast_single_ray(ray_id, ray_angle, data);
		i++;
		ray_angle += FOV_ANGLE / data->w_width;
		ray_id++;
	}
}