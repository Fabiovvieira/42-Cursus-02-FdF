/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 10:45:55 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/15 14:04:17 by fvalli-v         ###   ########.fr       */
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
# define RROT 114 //r
# define LROT 116 //t
# define ESC 65307 //ESC
# define PROJECTION 65289 //TAB

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width_map;
	int		height_map;
	int		**map;
	int		zoom;
	int		color;
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
