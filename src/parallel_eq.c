/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_eq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:18:20 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/18 14:19:20 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_iso_res	parallel(t_data *img, t_iso_res res)
{
	res = scale(img, res);
	res = translate(img, res);
	return (res);
}
