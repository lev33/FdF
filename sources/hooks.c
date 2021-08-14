/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:04:39 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/03/03 10:48:35 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_macos.h"
#include <stdlib.h>

int			win_close(void *param)
{
	(void)param;
	exit(0);
}

int			key_press(int key, void *param)
{
	t_map	*map;

	map = (t_map *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == NUM_PAD_PLUS || key == MAIN_PAD_PLUS
			|| key == NUM_PAD_MINUS || key == MAIN_PAD_MINUS)
		zoom(key, map);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
			|| key == ARROW_UP || key == ARROW_DOWN)
		move(key, map);
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
			|| key == NUM_PAD_2 || key == MAIN_PAD_2
			|| key == NUM_PAD_3 || key == MAIN_PAD_3
			|| key == NUM_PAD_4 || key == MAIN_PAD_4
			|| key == NUM_PAD_6 || key == MAIN_PAD_6
			|| key == NUM_PAD_7 || key == MAIN_PAD_7
			|| key == NUM_PAD_8 || key == MAIN_PAD_8
			|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		rotate(key, map);
	else if (key == MAIN_PAD_LESS || key == MAIN_PAD_MORE)
		flatten(key, map);
	else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
		change_projection(key, map);
	return (0);
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_map	*map;

	(void)x;
	(void)y;
	map = (t_map *)param;
	if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DOWN)
		zoom(button, map);
	else if (button == MOUSE_LEFT_BUTTON)
	{
		map->mouse_x = x;
		map->mouse_y = y;
		map->mouse_is_pressed = 1;
	}
	return (0);
}

int			mouse_release(int button, int x, int y, void *param)
{
	t_map	*map;

	(void)x;
	(void)y;
	(void)button;
	map = (t_map *)param;
	map->mouse_is_pressed = 0;
	return (0);
}

int			mouse_move(int x, int y, void *param)
{
	t_map	*map;
	int		cur_x;
	int		cur_y;

	map = (t_map *)param;
	cur_x = map->mouse_x;
	cur_y = map->mouse_y;
	if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		map->mouse_x = x;
		map->mouse_y = y;
		if (map->mouse_is_pressed)
		{
			map->beta += (x - cur_x) * 0.002;
			map->alpha += (y - cur_y) * 0.002;
			draw_map(map);
		}
	}
	else
		map->mouse_is_pressed = 0;
	return (0);
}
