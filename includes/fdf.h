/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ligeorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 10:27:23 by ligeorgi          #+#    #+#             */
/*   Updated: 2020/02/04 10:30:58 by ligeorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H

# define FDF_H

# define HEIGHT			1200
# define WIDTH			1450
# define MENU_WIDTH		250

# define TEXT_COLOR		0xEAEAEA
# define TEXT_COLOR1	0xFFFF00
# define BACKGROUND		0x222222
# define MENU_COLOR     0x1E1E1E

# define COLOR_1		0x008000
# define COLOR_2		0xA52A2A
# define COLOR_3		0xFFFFFF

typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

typedef struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					color;
}						t_point;

typedef struct			s_map
{
	int					width;
	int					height;
	int					*z;
	int					*color;
	int					is_color;
	int					z_min;
	int					z_max;
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					zoom;
	t_projection		projection;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	int					x_offset;
	int					y_offset;
	int					mouse_is_pressed;
	int					mouse_x;
	int					mouse_y;
}						t_map;

void					read_map(const int fd, t_map *map);
void					draw_map(t_map *map);
int						get_default_color(int z, t_map *map);
int						get_color(t_point cur, t_point start, t_point end,
															t_point delta);
t_point					project(t_point p, t_map *map);
int						win_close(void *param);
int						key_press(int key, void *param);
int						mouse_press(int button, int x, int y, void *param);
int						mouse_release(int button, int x, int y, void *param);
int						mouse_move(int x, int y, void *param);
void					zoom(int key, t_map *map);
void					move(int key, t_map *map);
void					rotate(int key, t_map *map);
void					flatten(int key, t_map *map);
void					change_projection(int key, t_map *map);
int						ft_isnumber(char *str, int base);
int						ft_atoi_base(const char *str, int base);
double					rate(int a, int b, int c);
void					throw(char *s);

#endif
