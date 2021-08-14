/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:03:49 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/02/04 10:07:58 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double		rate(int a, int b, int c)
{
	double	part;
	double	all;

	part = c - a;
	all = b - a;
	return ((a == b) ? 1.0 : part / all);
}

int			get_default_color(int z, t_map *map)
{
	double	percentage;

	percentage = rate(map->z_min, map->z_max, z);
	if (percentage < 0.33)
		return (COLOR_1);
	else if (percentage < 0.66)
		return (COLOR_2);
	else
		return (COLOR_3);
}

static int	set_color(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			get_color(t_point cur, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (cur.color == end.color)
		return (cur.color);
	if (delta.x > delta.y)
		percentage = rate(start.x, end.x, cur.x);
	else
		percentage = rate(start.y, end.y, cur.y);
	red = set_color((start.color >> 16) & 0xFF,
			(end.color >> 16) & 0xFF,
			percentage);
	green = set_color((start.color >> 8) & 0xFF,
			(end.color >> 8) & 0xFF,
			percentage);
	blue = set_color(start.color & 0xFF,
			end.color & 0xFF,
			percentage);
	return ((red << 16) | (green << 8) | blue);
}
