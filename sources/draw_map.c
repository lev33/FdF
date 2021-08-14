/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 09:57:07 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/03/03 10:46:38 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "mlx.h"

static void		print_menu(t_map *map)
{
	int			y;
	void		*mlx;
	void		*win;

	y = 0;
	mlx = map->mlx;
	win = map->win;
	mlx_string_put(mlx, win, 75, y += 20, TEXT_COLOR1, "Keyboard");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Esc        exit");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Arrows     move");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "+ -        zoom");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "< >        resize z");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "I P change projection");
	mlx_string_put(mlx, win, 75, y += 45, TEXT_COLOR1, " Numpad");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, " 8");
	mlx_string_put(mlx, win, 15, y += 14, TEXT_COLOR, "           rotation");
	mlx_string_put(mlx, win, 15, y += 14, TEXT_COLOR, " 2");
	mlx_string_put(mlx, win, 15, y += 40, TEXT_COLOR, "4 6        rotation");
	mlx_string_put(mlx, win, 15, y += 40, TEXT_COLOR, "  9");
	mlx_string_put(mlx, win, 15, y += 14, TEXT_COLOR, "           rotation");
	mlx_string_put(mlx, win, 15, y += 14, TEXT_COLOR, "1");
	mlx_string_put(mlx, win, 85, y += 40, TEXT_COLOR1, "Mouse");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Scroll        zoom");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Press & Move  rotation");
}

static void		put_pixel(t_map *map, int x, int y, int color)
{
	int			i;

	if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * map->bits_per_pixel / 8) + (y * map->size_line);
		map->data_addr[i] = color;
		map->data_addr[++i] = color >> 8;
		map->data_addr[++i] = color >> 16;
	}
}

static void		draw_line(t_point a, t_point b, t_map *map)
{
	t_point		d;
	t_point		dir;
	t_point		cur;

	d.x = a.x > b.x ? a.x - b.x : b.x - a.x;
	d.y = a.y > b.y ? a.y - b.y : b.y - a.y;
	d.z = d.x - d.y;
	dir.x = a.x > b.x ? -1 : 1;
	dir.y = a.y > b.y ? -1 : 1;
	cur = a;
	while (cur.x != b.x || cur.y != b.y)
	{
		put_pixel(map, cur.x, cur.y, get_color(cur, a, b, d));
		if ((dir.z = d.z * 2) > -d.y)
		{
			d.z -= d.y;
			cur.x += dir.x;
		}
		if (dir.z < d.x)
		{
			d.z += d.x;
			cur.y += dir.y;
		}
	}
}

static t_point	get_point(int x, int y, t_map *map)
{
	t_point		p;
	int			i;

	i = x + y * map->width;
	p.x = x;
	p.y = y;
	p.z = map->z[i];
	p.color = map->is_color ? map->color[i] : get_default_color(p.z, map);
	return (p);
}

void			draw_map(t_map *map)
{
	int			x;
	int			y;
	int			*data;

	data = (int *)map->data_addr;
	ft_bzero(map->data_addr, WIDTH * HEIGHT * (map->bits_per_pixel / 8));
	x = -1;
	while (++x < HEIGHT * WIDTH)
		data[x] = (x % WIDTH < MENU_WIDTH) ? MENU_COLOR : BACKGROUND;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (x != map->width - 1)
				draw_line(project(get_point(x, y, map), map),
						project(get_point(x + 1, y, map), map), map);
			if (y != map->height - 1)
				draw_line(project(get_point(x, y, map), map),
						project(get_point(x, y + 1, map), map), map);
		}
	}
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	print_menu(map);
}
