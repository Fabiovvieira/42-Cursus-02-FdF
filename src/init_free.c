/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_&_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:05:24 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/18 14:08:27 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_t_iso(t_data *data)
{
	data->iso.scale = 10;
	data->iso.transl_x = data->w_img / 2;
	data->iso.transl_y = data->h_img / 2;
	data->iso.rot_z = 0.;
	data->iso.rot_y = 0.;
	data->iso.rot_x = 0.61;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	data->w_img = 1920;
	data->h_img = 1080;
	data->mlx_win = mlx_new_window(data->mlx, data->w_img, data->h_img, "FDF");
	data->img = mlx_new_image(data->mlx, data->w_img, data->h_img);
	data->addr = NULL;
	data->bpp = 0;
	data->line_l = 0;
	data->endian = 0;
	data->w_map = 0;
	data->h_map = 0;
	data->map = NULL;
	init_t_iso(data);
	data->proj = 1;
	data->color = 0x0000FFFF;
	return (data);
}

void	free_split(char **list)
{
	int		i;

	i = 0;
	if (list == NULL)
		return ;
	while (list[i])
	{
		free(list[i]);
		i++;
	}
	free(list);
}

void	free_map(t_data *img)
{
	int		i;

	i = 0;
	if (img->map == NULL)
		return ;
	while (i < img->h_map)
	{
		free(img->map[i]);
		i++;
	}
	free(img->map);
}

int	ft_close(t_data *vars)
{
	if (vars)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free_map(vars);
		free(vars);
	}
	exit (EXIT_SUCCESS);
}
