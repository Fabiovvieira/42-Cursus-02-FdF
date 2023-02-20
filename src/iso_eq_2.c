/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso_eq_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:10:26 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/20 09:44:47 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_iso_res	rotate_z(t_data *img, t_iso_res res)
{
	t_iso_res	rot;

	rot.x = res.x * cos(img->iso.rot_z) - res.y * sin(img->iso.rot_z);
	rot.y = res.x * sin(img->iso.rot_z) + res.y * cos(img->iso.rot_z);
	rot.z = res.z;
	return (rot);
}

t_iso_res	rotate_y(t_data *img, t_iso_res res)
{
	t_iso_res	rot;

	rot.x = res.x * cos(img->iso.rot_y) + res.z * sin(img->iso.rot_y);
	rot.z = -res.x * sin(img->iso.rot_y) + res.z * cos(img->iso.rot_y);
	rot.y = res.y;
	return (rot);
}

t_iso_res	rotate_x(t_data *img, t_iso_res res)
{
	t_iso_res	rot;

	rot.y = res.y * cos(img->iso.rot_x) - res.z * sin(img->iso.rot_x);
	rot.z = res.y * sin(img->iso.rot_x) + res.z * cos(img->iso.rot_x);
	rot.x = res.x;
	return (rot);
}

t_iso_res	translate(t_data *img, t_iso_res res)
{
	t_iso_res	transl;

	transl.x = res.x + img->iso.transl_x;
	transl.y = res.y + img->iso.transl_y;
	transl.z = res.z;
	return (transl);
}

t_iso_res	scale(t_data *img, t_iso_res res)
{
	t_iso_res	scale;

	scale.x = res.x * img->iso.scale;
	scale.y = res.y * img->iso.scale;
	scale.z = res.z * img->iso.scale;
	return (scale);
}
