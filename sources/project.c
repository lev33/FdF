/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 09:50:11 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/02/04 09:50:17 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

static void	rotate_x(int *y, int *z, double alpha)
{
	int previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

static void	rotate_z(int *x, int *y, double gamma)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

static void	iso(int *x, int *y, int z)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = -z + (previous_x + previous_y) * sin(0.523599);
}

t_point		project(t_point p, t_map *map)
{
	p.x *= map->zoom;
	p.y *= map->zoom;
	p.z *= map->zoom / map->z_divisor;
	p.x -= (map->width * map->zoom) / 2;
	p.y -= (map->height * map->zoom) / 2;
	rotate_x(&p.y, &p.z, map->alpha);
	rotate_y(&p.x, &p.z, map->beta);
	rotate_z(&p.x, &p.y, map->gamma);
	if (map->projection == ISO)
		iso(&p.x, &p.y, p.z);
	p.x += (WIDTH - MENU_WIDTH) / 2 + map->x_offset + MENU_WIDTH;
	p.y += (HEIGHT + map->height * map->zoom) / 2 + map->y_offset;
	return (p);
}
