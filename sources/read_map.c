/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 09:50:45 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/03/03 10:47:15 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>

static void		free_arr(char **arr)
{
	size_t		i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

static void		list_to_map(t_list **tmp, t_map *map)
{
	t_list		*cur;
	ssize_t		i;
	size_t		z_size;
	char		**z_and_color;

	z_size = map->width * map->height * sizeof(int);
	if (!(map->z = (int *)ft_memalloc(z_size)))
		throw("ft_memalloc error");
	if (!(map->color = (int *)ft_memalloc(z_size)))
		throw("ft_memalloc error");
	i = map->width * map->height;
	while (--i >= 0)
	{
		cur = *tmp;
		*tmp = (*tmp)->next;
		z_and_color = (char **)cur->content;
		map->z[i] = ft_atoi(z_and_color[0]);
		map->color[i] = z_and_color[1] ? ft_atoi_base(z_and_color[1], 16) : -1;
		if (map->z[i] > map->z_max)
			map->z_max = map->z[i];
		if (map->z[i] < map->z_min)
			map->z_min = map->z[i];
		free_arr(z_and_color);
		free(cur);
	}
}

static t_list	*get_list(char *zc, t_map *map)
{
	t_list		*cur;
	char		**z_and_color;

	if (!(cur = (t_list *)ft_memalloc(sizeof(t_list))))
		throw("ft_memalloc error");
	if (!(z_and_color = ft_strsplit(zc, ','))
			|| !ft_isnumber(z_and_color[0], 10)
			|| (z_and_color[1] && !ft_isnumber(z_and_color[1], 16)))
		throw("Map reading error");
	if (z_and_color[1] && ft_strlen(z_and_color[1]) != 8)
		throw("Invalid Hexadecimal color code");
	cur->content = (void *)z_and_color;
	cur->content_size = 0;
	cur->next = NULL;
	(z_and_color[1]) ? map->is_color = 1 : 0;
	return (cur);
}

static void		zc_to_list(char **zc, t_list **tmp, t_map *map)
{
	int			width;

	width = 0;
	while (*zc)
	{
		ft_lstadd(tmp, get_list(*zc++, map));
		width++;
	}
	if (!map->height)
		map->width = width;
	else if (map->width != width)
		throw("Incorrect map file");
}

void			read_map(const int fd, t_map *map)
{
	char		*line;
	int			result;
	char		**z_and_color;
	t_list		*tmp;

	map->width = 0;
	map->height = 0;
	map->z = NULL;
	map->color = NULL;
	map->is_color = 0;
	map->z_min = (int)((unsigned)(~0L) >> 1);
	map->z_max = (int)(~map->z_min);
	tmp = NULL;
	while ((result = get_next_line(fd, &line)) == 1)
	{
		if (!(z_and_color = ft_strsplit(line, ' ')))
			throw("Map reading error");
		zc_to_list(z_and_color, &tmp, map);
		free_arr(z_and_color);
		ft_strdel(&line);
		map->height++;
	}
	if (!tmp || result == -1)
		throw("Incorrect map file");
	list_to_map(&tmp, map);
}
