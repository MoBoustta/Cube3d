/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 14:54:35 by moboustt          #+#    #+#             */
/*   Updated: 2020/02/15 14:54:37 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		key_pressed(int keycode, t_struct *data)
{
	if (keycode == 53)
		ft_close(data);
	if (keycode == 126)
		data->walk_direction = 1;
	if (keycode == 125)
		data->walk_direction = -1;
	if (keycode == 124)
		data->turn_direction = 1;
	if (keycode == 123)
		data->turn_direction = -1;
	return (TRUE);
}

int		key_released(int keycode, t_struct *data)
{
	if (keycode == 126)
		data->walk_direction = 0;
	if (keycode == 125)
		data->walk_direction = 0;
	if (keycode == 124)
		data->turn_direction = 0;
	if (keycode == 123)
		data->turn_direction = 0;
	return (TRUE);
}

int		ft_close(void *param)
{
	(void)param;
	exit(0);
}