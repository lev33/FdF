/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:00:34 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/02/04 10:24:17 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"

void			throw(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

static void		run_loop(t_map *map)
{
	mlx_hook(map->win, 2, 0, key_press, map);
	mlx_hook(map->win, 17, 0, win_close, map);
	mlx_hook(map->win, 4, 0, mouse_press, map);
	mlx_hook(map->win, 5, 0, mouse_release, map);
	mlx_hook(map->win, 6, 0, mouse_move, map);
	mlx_loop(map->mlx);
}

static void		get_mlx(t_map *map)
{
	if (!(map->mlx = mlx_init()))
		throw("MiniLibX initialization error");
	if (!(map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "FdF")))
		throw("MiniLibX initialization error");
	if (!(map->img = mlx_new_image(map->mlx, WIDTH, HEIGHT)))
		throw("MiniLibX initialization error");
	map->data_addr = mlx_get_data_addr(map->img, &(map->bits_per_pixel),
			&(map->size_line), &(map->endian));
	map->zoom =
		(WIDTH - MENU_WIDTH) / map->width / 2 < HEIGHT / map->height / 2 ?
		(WIDTH - MENU_WIDTH) / map->width / 2 : HEIGHT / map->height / 2;
	map->alpha = 0;
	map->beta = 0;
	map->gamma = 0;
	map->z_divisor = 1;
	map->x_offset = 0;
	map->y_offset = 0;
}

int				main(int argc, char **argv)
{
	int			fd;
	t_map		*map;

	errno = 0;
	if (argc == 2)
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
			throw("Incorrect map file");
		if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
			throw("t_map ft_memalloc error");
		read_map(fd, map);
		close(fd);
		get_mlx(map);
		draw_map(map);
		run_loop(map);
	}
	throw("Usage: ./fdf map_file");
	return (0);
}
