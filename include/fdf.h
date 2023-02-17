/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:45:55 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/17 10:56:47 by fvalli-v         ###   ########.fr       */
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

/* ---------COLOR--------- */
# define GREEN 0x0000FFF00

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
	int		color;
	int		proj;
	t_iso	iso;
}		t_data;

#endif
