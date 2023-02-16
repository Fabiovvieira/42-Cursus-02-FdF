/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:45:55 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/16 11:00:36 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
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

typedef struct	s_iso {
	int		scale;
	int		transl_x;
	int		transl_y;
	float	rot_z;
	float	rot_y;
	float	rot_x;
}		t_iso;

typedef struct	s_iso_res {
	int	x;
	int	y;
	int	z;
}		t_iso_res;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	int		width_img;
	int		height_img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_map;
	int		height_map;
	int		**map;
	int		color;
	int		proj;
	t_iso	iso;
}		t_data;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
}		t_window;

typedef struct s_img
{
	t_window	*win;
	void		*img_ptr;
	char		*addr;
	int			h;
	int			w;
	int			bpp;
	int			endian;
	int			line_len;
}		t_img;

typedef struct s_fdf
{
	t_img	*img;
	int		width_map;
	int		height_map;
	int		**map;
	int		zoom;
}		t_fdf;

#endif
