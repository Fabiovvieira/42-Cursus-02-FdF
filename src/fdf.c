/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/15 23:13:42 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


t_iso_res	isometric(t_data *img, int x, int y, int z)
{
	float	x0;
	float	y0;
	float	z0;
	// (void)z;
	// ft_printf("x = %d | y = %d\n",x, y);
	//scaling
	x0 = x * img->iso.scale;
	y0 = y * img->iso.scale;
	z0 = z;
	// x0 = x;
	// y0 = y;

	//isometric matrix
	x = x0 * cos(0.80) - y0 * sin(0.80);
	y = y0 * cos(0.80) + z0 + x0 * sin(0.80);
	// x = x0 * cos(0.8) - y0 * sin(0.8);
	// y = y0 * cos(0.8) + x0 * sin(0.8);

	//rotate around z axis
	x0 = x * cos(img->iso.rot_z) - y * sin(img->iso.rot_z);
	y0 = x * sin(img->iso.rot_z) + y * cos(img->iso.rot_z);

	// //rotate around y axis
	x = x0 * cos(img->iso.rot_y) + z0 * sin(img->iso.rot_y);
	z = -x0 * sin(img->iso.rot_y) + z0 * cos(img->iso.rot_y);
	y = y0;

	// //rotate around x axis
	y0 = y * cos(img->iso.rot_x) - z * sin(img->iso.rot_x);
	z0 = y * sin(img->iso.rot_x) + z * cos(img->iso.rot_x);
	x0 = x;

	//translate
	x = x0 + img->iso.transl_x;
	y = y0 + img->iso.transl_y;
	z = z0;
	return((t_iso_res){x, y, z});
}


void	draw_a_line(t_data *img, int x0, int y0, int x1, int y1)
{
	float	dx, dy, x, y;
	int		pixels;
	int		len;
	t_iso_res	res, res1;
	int z0, z1;
	z0 = -img->map[y0][x0];
	z1 = -img->map[y1][x1];
	// (void)z1;

	// 	//isometric
	res = isometric(img, x0, y0, z0);
	res1 = isometric(img, x1, y1, z1);
	x0 = res.x;
	y0 = res.y;
	z0 = res.z;
	x1 = res1.x;
	y1 = res1.y;
	z1 = res1.z;

	//color
	if(z0)
		img->color = 0x00FF0000;
	else
		img->color = 0x0000FFFF;

	dx = (float)x1 - (float)x0;
	dy = (float)y1 - (float)y0;
	pixels = sqrt((dx * dx) + (dy * dy));
	len = pixels;
	(void)len;
	dx /= pixels;
	dy /= pixels;
	x = x0;
	y = y0;
	while (pixels > 0)
	{
		my_mlx_pixel_put(img, (int)x, (int)y, img->color);
		x += dx;
		y += dy;
		pixels = pixels - 1;
	}
}


t_data	*init_data(void)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Hello world!");
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->width_map = 0;
	data->height_map = 0;
	data->map = NULL;
	data->iso.scale = 20;
	data->iso.transl_x = 200;
	data->iso.transl_y = 200;
	data->iso.rot_z = 0.;
	data->iso.rot_y = 0.;
	data->iso.rot_z = 0.;
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

int	word_count(char	**strs)
{
	int	count;

	count = 0;
	while(strs[count])
		count++;
	return (count);
}

void	get_sizemap(t_data *img, char *mapfile)
{
	int		fd;
	char	*str;
	char	**strs;
	int		line;

	line = 0;
	fd = open (mapfile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening mapfile.");
		exit(1);
	}
	str = get_next_line(fd);
	line++;
	strs = ft_split(str, ' ');
	free(str);
	img->width_map = word_count(strs);
	while ((str = get_next_line(fd)))
	{
		free(str);
		line++;
	}
	img->height_map = line;
	free_split(strs);
	free(str);
	close(fd);
}

void	parse_map(t_data *img, char *mapfile)
{
	int	fd;
	int	**map;
	int	i;
	int	j;
	char	*str;
	char	**strs;

	j = 0;
	i = 0;
	map = (int **)malloc(sizeof(int *) * img->height_map);
	fd = open (mapfile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening mapfile.");
		exit(1);
	}
	while (i < img->height_map)
	{
		str = get_next_line(fd);
		strs = ft_split(str, ' ');
		map[i] = (int *)malloc(sizeof(int) * img->width_map);
		while (j < img->width_map)
		{
			map[i][j] = ft_atoi(strs[j]);
			j++;
		}
		j = 0;
		free_split(strs);
		free(str);
		i++;
	}
	str = get_next_line(fd);
	free(str);
	img->map = map;
	close(fd);
}

void	free_map(t_data *img)
{
	int		i;

	i = 0;
	if (img->map == NULL)
		return ;
	while (i < img->height_map)
	{
		free(img->map[i]);
		i++;
	}
	free(img->map);
}

void	print_map(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->height_map)
	{
		while (j < img->width_map)
		{
			ft_printf("%3d ", img->map[i][j]);
			j++;
		}
		ft_printf("\n");
		j = 0;
		i++;
	}
}

void	draw_file(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height_map)
	{
		x = 0;
		while (x < img->width_map)
		{
			if (x < img->width_map - 1)
				draw_a_line(img, x, y, x + 1, y);
			if (y < img->height_map - 1)
				draw_a_line(img, x, y, x, y + 1);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	read_map(t_data *img, char *mapfile)
{
	int	fd;

	fd = open (mapfile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening mapfile.");
		exit(1);
	}
	get_sizemap(img, mapfile);
	parse_map(img, mapfile);
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

void	print_line(int x, int y, t_data *img)
{
	// mlx_clear_window(img->mlx, img->mlx_win);
	// (void)x;
	// (void)y;
	draw_a_line(img, x, y, 2 * x, 2 * y);
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

int	deal_key(int key, void *data)
{
	t_data	*img;
	// static int x = 100, y = 100;

	img = (t_data *)data;
	if (key == ESC)
		ft_close(img);
	else if (key == ZOOMIN)
	{
		img->iso.scale += 2;
	}
	else if (key == ZOOMOUT)
	{
		img->iso.scale -= 2;
	}
	else if (key == UP)
	{
		img->iso.transl_y -= 1;
	}
	else if (key == DOWN)
	{
		img->iso.transl_y += 10;
	}
	else if (key == LEFT)
	{
		img->iso.transl_x -= 10;
	}
	else if (key == RIGHT)
	{
		img->iso.transl_x += 10;
	}
	else if (key == ZP_ROT)
	{
		img->iso.rot_z += 0.1;
	}
	else if (key == ZM_ROT)
	{
		img->iso.rot_z -= 0.1;
	}
	else if (key == YP_ROT)
	{
		img->iso.rot_y += 0.1;
	}
	else if (key == YM_ROT)
	{
		img->iso.rot_y -= 0.1;
	}
	else if (key == XP_ROT)
	{
		img->iso.rot_x += 0.1;
	}
	else if (key == XM_ROT)
	{
		img->iso.rot_x -= 0.1;
	}
	else
		ft_printf("key pressed = %d\n", key);
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, 1920, 1080);
	draw_file(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	return(0);
}



int read_mouse(int button, int mouse_x, int mouse_y, void *param)
{
	int 		x;
	int 		y;
	t_data 		*img;

	img = (t_data *) param;
	if (!img)
		return (-1);
	if (mouse_x < 0 || mouse_y < 0 || mouse_x > img->width_map || mouse_y > img->height_map)
		return (2);
	x = (mouse_x % img->width_map);
	y = (mouse_y % img->height_map);
	ft_printf("mouse_x = %d | mouse_y = %d", x, y);
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	(void)button;
	return (0);
}

int	main(int argc , char **argv)
{
	t_data	*img;
	// int	i = 0;
	// int	x = 100, y=100;
	int	x;
	int	y;


	img = init_data();
	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error on input. Try again: \"./fdf map.fdf\"\n");
		return (0);
	}
	read_map(img, argv[1]);
	print_map(img);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), &(img->line_length),
								&(img->endian));
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	draw_file(img);
	// draw_a_line(img, 100, 100, 500, 500);
	// draw_a_line(img, 200, 200, 100, 300);
	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);


	// mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	// mlx_mouse_hook (img->mlx_win, read_mouse, img);

	mlx_get_screen_size(img->mlx, &x, &y);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_key_hook(img->mlx_win, deal_key, img);
	mlx_loop(img->mlx);
	free(img);
	return (0);
}
