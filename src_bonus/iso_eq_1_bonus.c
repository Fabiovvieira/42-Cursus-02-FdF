/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_eq_1_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:10:23 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:10:18 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_iso_res	iso_projection(t_iso_res res)
{
	t_iso_res	iso;

	iso.x = res.x * cos(0.8) - res.y * sin(0.8);
	iso.y = res.y * cos(0.8) + res.x * sin(0.8);
	iso.z = res.z;
	return (iso);
}

t_iso_res	isometric(t_data *img, t_iso_res res)
{
	res = scale(img, res);
	res = iso_projection(res);
	res = rotate_z(img, res);
	res = rotate_y(img, res);
	res = rotate_x(img, res);
	res = translate(img, res);
	return (res);
}
