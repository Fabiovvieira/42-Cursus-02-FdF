/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/22 09:10:01 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	draw_file_iso(img);
	draw_menu(img);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_hook(img->mlx_win, 2, (1L << 0), deal_key, img);
	mlx_loop(img->mlx);
	free(img);
	return (0);
}
