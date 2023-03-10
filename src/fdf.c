/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 11:08:33 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	openfile(char *mapfile)
{
	int	fd;

	fd = open (mapfile, O_RDONLY, 0);
	if (fd < 0)
	{
		perror("Error on opening mapfile.");
		exit(1);
	}
	return (fd);
}

void	init_centered(t_data *img)
{
	int	square;

	square = (int)sqrt(img->w_map * img->w_map + img->h_map * img->h_map);
	img->iso.transl_y = (img->h_img / 2) - img->iso.scale * ((square) / 2);
}

int	main(int argc, char **argv)
{
	t_data	*img;

	img = init_data();
	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error on input. Try again: \"./fdf map.fdf\"\n");
		ft_close(img);
		return (0);
	}
	read_map(img, argv[1]);
	get_max_min_z(img);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp), &(img->line_l),
			&(img->endian));
	init_centered(img);
	draw_file_iso(img);
	draw_menu(img);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_hook(img->mlx_win, 2, (1L << 0), deal_key, img);
	mlx_loop(img->mlx);
	free(img);
	return (0);
}
