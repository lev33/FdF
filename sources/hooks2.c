/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:05:00 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/02/04 10:05:06 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "key_macos.h"

void	zoom(int key, t_map *map)
{
	if (key == NUM_PAD_PLUS ||
		key == MAIN_PAD_PLUS ||
		key == MOUSE_SCROLL_UP)
		map->zoom++;
	else if (key == NUM_PAD_MINUS ||
		key == MAIN_PAD_MINUS ||
		key == MOUSE_SCROLL_DOWN)
		map->zoom--;
	if (map->zoom < 1)
		map->zoom = 1;
	draw_map(map);
}

void	move(int key, t_map *map)
{
	if (key == ARROW_LEFT)
		map->x_offset -= 10;
	else if (key == ARROW_RIGHT)
		map->x_offset += 10;
	else if (key == ARROW_UP)
		map->y_offset -= 10;
	else
		map->y_offset += 10;
	draw_map(map);
}

void	rotate(int key, t_map *map)
{
	if (key == NUM_PAD_2 || key == MAIN_PAD_2)
		map->alpha += 0.05;
	else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
		map->alpha -= 0.05;
	else if (key == NUM_PAD_4 || key == MAIN_PAD_4)
		map->beta -= 0.05;
	else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
		map->beta += 0.05;
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_3 || key == MAIN_PAD_3)
		map->gamma += 0.05;
	else if (key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		map->gamma -= 0.05;
	draw_map(map);
}

void	flatten(int key, t_map *map)
{
	if (key == MAIN_PAD_LESS)
		map->z_divisor += 0.1;
	else if (key == MAIN_PAD_MORE)
		map->z_divisor -= 0.1;
	if (map->z_divisor < 0.1)
		map->z_divisor = 0.1;
	else if (map->z_divisor > 10)
		map->z_divisor = 10;
	draw_map(map);
}

void	change_projection(int key, t_map *map)
{
	map->alpha = 0;
	map->beta = 0;
	map->gamma = 0;
	if (key == MAIN_PAD_I)
		map->projection = ISO;
	else if (key == MAIN_PAD_P)
		map->projection = PARALLEL;
	draw_map(map);
}
