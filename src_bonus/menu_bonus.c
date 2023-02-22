/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 13:54:20 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:10:28 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	put_str_img(t_data *img, int x, int y, char *str)
{
	mlx_string_put(img->mlx, img->mlx_win, x, y, GREEN, str);
}

void	draw_menu(t_data *img)
{
	put_str_img(img, 65, 50, "How to Use:");
	put_str_img(img, 65, 80, "Zoom:");
	put_str_img(img, 65, 100, "Zoom In: 'i'");
	put_str_img(img, 65, 120, "Zoom Out: 'o'");
	put_str_img(img, 65, 170, "Translate map:");
	put_str_img(img, 65, 190, "Move up: 'w'");
	put_str_img(img, 65, 210, "Move down: 's'");
	put_str_img(img, 65, 230, "Move right: 'd'");
	put_str_img(img, 65, 250, "Move left: 'a'");
	put_str_img(img, 65, 300, "Rotation in X/Y/Z axis");
	put_str_img(img, 65, 320, "Rotate CW z-axis: 'r'");
	put_str_img(img, 65, 340, "Rotate CCW z-axis: 't'");
	put_str_img(img, 65, 360, "Rotate CW y-axis: 'f'");
	put_str_img(img, 65, 380, "Rotate CCW y-axis: 'g'");
	put_str_img(img, 65, 400, "Rotate CW x-axis: 'v'");
	put_str_img(img, 65, 420, "Rotate CCW x-axis: 'b'");
	put_str_img(img, 65, 470, "Change projections: press 'TAB'");
	put_str_img(img, 65, 520, "Close Windows:");
	put_str_img(img, 65, 540, "Press 'ESC' or ");
	put_str_img(img, 65, 560, "Click on the cross.");
}
