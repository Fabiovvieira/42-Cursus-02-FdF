/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:45:55 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:46:34 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include "libft.h"
# include <stdlib.h>
# include <limits.h>
# include "mlx.h"
# include <math.h>

# define ZOOMIN 105 //i
# define ZOOMOUT 111 //o
# define UP 119 //w
# define DOWN 115 //s
# define LEFT 97 //a
# define RIGHT 100 //d
# define ZP_ROT 114 //r
# define ZM_ROT 116 //t
# define YP_ROT 102 //f
# define YM_ROT 103 //g
# define XP_ROT 118 //v
# define XM_ROT 98 //b
# define ESC 65307 //ESC
# define PROJECTION 65289 //TAB

/* ---------COLOR--------- */
# define GREEN 0x0000FF00
# define CMIN 0x000000FF
# define CMAX 0x00FFFF00

typedef struct s_point {
	int	x;
	int	y;
}		t_point;

typedef struct s_iso {
	int		scale;
	int		transl_x;
	int		transl_y;
	float	rot_z;
	float	rot_y;
	float	rot_x;
}		t_iso;

typedef struct s_iso_res {
	float	x;
	float	y;
	float	z;
}		t_iso_res;

typedef struct s_color {
	float	c0;
	float	c1;
	float	step;
}		t_color;

typedef struct s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		w_img;
	int		h_img;
	char	*addr;
	int		bpp;
	int		line_l;
	int		endian;
	int		w_map;
	int		h_map;
	int		**map;
	int		zma;
	int		zmi;
	int		proj;
	t_iso	iso;
}		t_data;

/*menu.c*/
void		put_str_img(t_data *img, int x, int y, char *str);
void		draw_menu(t_data *img);

/*keys.c*/
void		op_translate(int key, t_data *img);
void		op_rotate(int key, t_data *img);
void		op_scale(int key, t_data *img);
int			check_keys(int key, t_data *img);
int			deal_key(int key, void *data);

/*init_free.c*/
void		init_t_iso(t_data *data);
t_data		*init_data(void);
void		free_split(char **list);
void		free_map(t_data *img);
int			ft_close(t_data *vars);

/*iso_eq_1.c*/
t_iso_res	iso_projection(t_iso_res res);
t_iso_res	isometric(t_data *img, t_iso_res res);

/*iso_eq_2.c*/
t_iso_res	rotate_z(t_data *img, t_iso_res res);
t_iso_res	rotate_y(t_data *img, t_iso_res res);
t_iso_res	rotate_x(t_data *img, t_iso_res res);
t_iso_res	translate(t_data *img, t_iso_res res);
t_iso_res	scale(t_data *img, t_iso_res res);

/*draw.c*/
void		draw_file_iso(t_data *img);
void		draw_file_2d(t_data *img);
void		draw_a_line_2d(t_data *img, t_point p0, t_point p1);
void		draw_a_line(t_data *img, t_point p0, t_point p1);

/*parallel.c*/
t_iso_res	parallel(t_data *img, t_iso_res res);

/*draw_utils.c*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			check_limits(t_data *img, int x, int y);
// void		draw_points(t_data *img, t_iso_res res0, t_iso_res res1);
void		draw_points(t_data *img, t_iso_res res0, t_iso_res res1, t_color c);

/*map.c*/
int			word_count(char	**strs);
void		get_sizemap(t_data *img, char *mapfile);
void		fill_map(t_data *img, int fd, int i, int j);
void		parse_map(t_data *img, char *mapfile);
void		read_map(t_data *img, char *mapfile);

/*fdf.c*/
int			openfile(char *mapfile);

/*color.c*/
void		get_max_min_z(t_data *img);

#endif
