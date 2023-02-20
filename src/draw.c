/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:14:21 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/20 21:58:46 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_file_iso(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->h_map)
	{
		x = 0;
		while (x < img->w_map)
		{
			if (x < img->w_map - 1)
				draw_a_line(img, (t_point){x, y}, (t_point){x + 1, y});
			if (y < img->h_map - 1)
				draw_a_line(img, (t_point){x, y}, (t_point){x, y + 1});
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	draw_file_2d(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->h_map)
	{
		x = 0;
		while (x < img->w_map)
		{
			if (x < img->w_map - 1)
				draw_a_line_2d(img, (t_point){x, y}, (t_point){x + 1, y});
			if (y < img->h_map - 1)
				draw_a_line_2d(img, (t_point){x, y}, (t_point){x, y + 1});
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	draw_a_line_2d(t_data *img, t_point p0, t_point p1)
{
	t_iso_res	res0;
	t_iso_res	res1;
	int			z0;
	int			z1;
	t_color		c;

	z0 = (img->map)[p0.y][p0.x];
	z1 = (img->map)[p1.y][p1.x];
	if (img->zma != img->zmi)
	{
		c.c0 = (float)((float)(z0 - img->zmi) / (float)(img->zma - img->zmi));
		c.c0 = (c.c0 * (CMAX - CMIN)) + CMIN;
		c.c1 = (float)((float)(z1 - img->zmi) / (float)(img->zma - img->zmi));
		c.c1 = (c.c1 * (CMAX - CMIN)) + CMIN;
	}
	else
	{
		c.c0 = CMIN;
		c.c1 = CMIN;
	}
	res0 = parallel(img, (t_iso_res){p0.x, p0.y, z0});
	res1 = parallel(img, (t_iso_res){p1.x, p1.y, z1});
	draw_points(img, res0, res1, c);
}

void	draw_a_line(t_data *img, t_point p0, t_point p1)
{
	t_iso_res	res0;
	t_iso_res	res1;
	int			z0;
	int			z1;
	t_color		c;

	z0 = img->map[p0.y][p0.x];
	z1 = img->map[p1.y][p1.x];
	if (img->zma != img->zmi)
	{
		c.c0 = (float)((float)(z0 - img->zmi) / (float)(img->zma - img->zmi));
		c.c0 = (c.c0 * (CMAX - CMIN)) + CMIN;
		c.c1 = (float)((float)(z1 - img->zmi) / (float)(img->zma - img->zmi));
		c.c1 = (c.c1 * (CMAX - CMIN)) + CMIN;
	}
	else
	{
		c.c0 = CMIN;
		c.c1 = CMIN;
	}
	res0 = isometric(img, (t_iso_res){p0.x, p0.y, z0});
	res1 = isometric(img, (t_iso_res){p1.x, p1.y, z1});
	draw_points(img, res0, res1, c);
}
