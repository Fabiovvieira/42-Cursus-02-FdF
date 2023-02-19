/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:01:03 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/19 18:54:09 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	op_translate(int key, t_data *img)
{
	if (key == UP)
		img->iso.transl_y -= 10;
	else if (key == DOWN)
		img->iso.transl_y += 10;
	else if (key == LEFT)
		img->iso.transl_x -= 10;
	else
		img->iso.transl_x += 10;
}

void	op_rotate(int key, t_data *img)
{
	if (key == ZP_ROT)
		img->iso.rot_z += 0.1;
	else if (key == ZM_ROT)
		img->iso.rot_z -= 0.1;
	else if (key == YP_ROT)
		img->iso.rot_y += 0.1;
	else if (key == YM_ROT)
		img->iso.rot_y -= 0.1;
	else if (key == XP_ROT)
		img->iso.rot_x += 0.1;
	else
		img->iso.rot_x -= 0.1;
}

void	op_scale(int key, t_data *img)
{
	if (key == ZOOMIN)
		img->iso.scale += 2;
	else
		if (img->iso.scale > 2)
			img->iso.scale -= 2;
}

int	check_keys(int key, t_data *img)
{
	if (key == ESC)
		ft_close(img);
	else if (key == ZOOMIN || key == ZOOMOUT)
		op_scale(key, img);
	else if (key == UP || key == DOWN || key == LEFT
		|| key == RIGHT)
		op_translate(key, img);
	else if (key == ZP_ROT || key == ZM_ROT || key == YP_ROT
		|| key == YM_ROT || key == XP_ROT || key == XM_ROT)
		op_rotate(key, img);
	else if (key == PROJECTION)
		img->proj *= -1;
	else
		return (0);
	return (1);
}

int	deal_key(int key, void *data)
{
	t_data	*img;

	img = (t_data *)data;
	if (!check_keys(key, img))
		return (0);
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, 1920, 1080);
	if (img->proj == 1)
		draw_file_iso(img);
	else
		draw_file_2d(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	draw_menu(img);
	return (0);
}
