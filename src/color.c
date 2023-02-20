/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:52:35 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/20 15:48:54 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
			if (img->map[j][i] < img->z_min)
				img->z_min = img->map[j][i];
			if (img->map[j][i] > img->z_max)
				img->z_max = img->map[j][i];
			i++;
		}
		j++;
	}
	// ft_printf("max = %d | min = %d\n", img->z_max, img->z_min);
}

// void	get_color(t_data *img, int x)
// {

// }
