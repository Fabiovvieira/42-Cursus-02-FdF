/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_eq_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:18:20 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:10:12 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

t_iso_res	parallel(t_data *img, t_iso_res res)
{
	res = scale(img, res);
	res = translate(img, res);
	return (res);
}
