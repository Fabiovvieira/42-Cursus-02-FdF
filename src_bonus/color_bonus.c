/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:52:35 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:09:38 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	get_max_min_z(t_data *img)
{
	int	i;
	int	j;

	j = 0;
	while (j < img->h_map)
	{
		i = 0;
		while (i < img->w_map)
		{
			if (img->map[j][i] < img->zmi)
				img->zmi = img->map[j][i];
			if (img->map[j][i] > img->zma)
				img->zma = img->map[j][i];
			i++;
		}
		j++;
	}
}
