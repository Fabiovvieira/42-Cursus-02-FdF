/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/17 11:29:48 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_l + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

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

t_iso_res	iso_projection(t_iso_res res)
{
	t_iso_res	iso;

	iso.x = res.x * cos(0.80) - res.y * sin(0.80);
	iso.y = res.y * cos(0.80) + res.z + res.x * sin(0.80);
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

int	check_limits(t_data *img, int x, int y)
{
	if (x < img->w_img && x > 0 && y < img->h_img && y > 0)
		return (1);
	else
		return (0);
}

void	draw_points(t_data *img, t_iso_res res0, t_iso_res res1)
{
	float	dx;
	float	dy;
	float	x;
	float	y;
	int		pixels;

	dx = (float)res1.x - (float)res0.x;
	dy = (float)res1.y - (float)res0.y;
	pixels = sqrt((dx * dx) + (dy * dy));
	dx /= pixels;
	dy /= pixels;
	x = res0.x;
	y = res0.y;
	while (pixels > 0)
	{
		if (check_limits(img, (int)x, (int)y))
			my_mlx_pixel_put(img, (int)x, (int)y, img->color);
		x += dx;
		y += dy;
		pixels = pixels - 1;
	}
}

void	draw_a_line(t_data *img, t_point p0, t_point p1)
{
	t_iso_res	res0;
	t_iso_res	res1;
	int			z0;
	int			z1;

	z0 = -img->map[p0.y][p0.x];
	z1 = -img->map[p1.y][p1.x];
	if (z0)
		img->color = 0x00FF0000;
	else
		img->color = 0x0000FFFF;
	res0 = isometric(img, (t_iso_res){p0.x, p0.y, z0});
	res1 = isometric(img, (t_iso_res){p1.x, p1.y, z1});
	draw_points(img, res0, res1);
}

t_iso_res	parallel(t_data *img, t_iso_res res)
{
	res = scale(img, res);
	res = translate(img, res);
	return (res);
}

void	draw_a_line_2d(t_data *img, t_point p0, t_point p1)
{
	t_iso_res	res0;
	t_iso_res	res1;
	int			z0;
	int			z1;

	z0 = -img->map[p0.y][p0.x];
	z1 = -img->map[p1.y][p1.x];
	if (z0)
		img->color = 0x00FF0000;
	else
		img->color = 0x0000FFFF;
	res0 = parallel(img, (t_iso_res){p0.x, p0.y, z0});
	res1 = parallel(img, (t_iso_res){p1.x, p1.y, z1});
	draw_points(img, res0, res1);
}

void	init_t_iso(t_data *data)
{
	data->iso.scale = 20;
	data->iso.transl_x = data->w_img / 2;
	data->iso.transl_y = data->h_img / 2;
	data->iso.rot_z = 0.;
	data->iso.rot_y = 0.;
	data->iso.rot_x = 0.;
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

int	word_count(char	**strs)
{
	int	count;

	count = 0;
	while (strs[count])
		count++;
	return (count);
}

int	openfile(char *mapfile)
{
	int	fd;

	fd = open (mapfile, O_RDONLY);
	if (fd < 0)
	{
		perror("Error on opening mapfile.");
		exit(1);
	}
	return (fd);
}

void	get_sizemap(t_data *img, char *mapfile)
{
	int		fd;
	char	*str;
	char	**strs;
	int		line;

	line = 0;
	fd = openfile(mapfile);
	str = get_next_line(fd);
	line++;
	strs = ft_split(str, ' ');
	free(str);
	img->w_map = word_count(strs);
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		free(str);
		line++;
	}
	img->h_map = line;
	free_split(strs);
	free(str);
	close(fd);
}

int	**fill_map(t_data *img, int fd, int i, int j)
{
	char	*str;
	char	**strs;
	int		**map;

	map = (int **)malloc(sizeof(int *) * img->h_map);
	if (!map)
		return (NULL);
	while (i < img->h_map)
	{
		str = get_next_line(fd);
		strs = ft_split(str, ' ');
		map[i] = (int *)malloc(sizeof(int) * img->w_map);
		while (j < img->w_map)
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
	return (map);
}

void	parse_map(t_data *img, char *mapfile)
{
	int		fd;
	int		i;
	int		j;

	j = 0;
	i = 0;
	fd = openfile(mapfile);
	img->map = fill_map(img, fd, i, j);
	close(fd);
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

void	draw_file_iso(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->h_map)
	{
		x = 0;
		while (x < img->w_map)
		{
			if (x < img->w_map - 1)
				draw_a_line(img, (t_point){x, y}, (t_point){x + 1, y});
			if (y < img->h_map - 1)
				draw_a_line(img, (t_point){x, y}, (t_point){x, y + 1});
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
}

void	draw_file_2d(t_data *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->h_map)
	{
		x = 0;
		while (x < img->w_map)
		{
			if (x < img->w_map - 1)
				draw_a_line_2d(img, (t_point){x, y}, (t_point){x + 1, y});
			if (y < img->h_map - 1)
				draw_a_line_2d(img, (t_point){x, y}, (t_point){x, y + 1});
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

void	put_str_img(t_data *img, int x, int y, char *str)
{
	mlx_string_put(img->mlx, img->mlx_win, x, y, GREEN, str);
}

void	draw_menu(t_data *img)
{
	put_str_img(img, 65, 50, "How to Use:");
	put_str_img(img, 65, 80, "Zoom:");
	put_str_img(img, 65, 100, "Zoom In: 'i'");
	put_str_img(img, 65, 120, "Zoom Out: 'o'");
	put_str_img(img, 65, 170, "Translate map:");
	put_str_img(img, 65, 190, "Move up: 'w'");
	put_str_img(img, 65, 210, "Move down: 's'");
	put_str_img(img, 65, 230, "Move right: 'd'");
	put_str_img(img, 65, 250, "Move left: 'a'");
	put_str_img(img, 65, 300, "Rotation in X/Y/Z axis");
	put_str_img(img, 65, 320, "Rotate CW z-axis: 'r'");
	put_str_img(img, 65, 340, "Rotate CCW z-axis: 't'");
	put_str_img(img, 65, 360, "Rotate CW y-axis: 'f'");
	put_str_img(img, 65, 380, "Rotate CCW y-axis: 'g'");
	put_str_img(img, 65, 400, "Rotate CW x-axis: 'v'");
	put_str_img(img, 65, 420, "Rotate CCW x-axis: 'b'");
	put_str_img(img, 65, 470, "Change projections: press 'TAB'");
	put_str_img(img, 65, 520, "Close Windows:");
	put_str_img(img, 65, 540, "Press 'ESC' or ");
	put_str_img(img, 65, 560, "Click on the cross.");
}

void	op_translate(int key, t_data *img)
{
	if (key == UP)
		img->iso.transl_y -= 10;
	else if (key == DOWN)
		img->iso.transl_y += 10;
	else if (key == LEFT)
		img->iso.transl_x -= 10;
	else
		img->iso.transl_x += 10;
}

void	op_rotate(int key, t_data *img)
{
	if (key == ZP_ROT)
		img->iso.rot_z += 0.1;
	else if (key == ZM_ROT)
		img->iso.rot_z -= 0.1;
	else if (key == YP_ROT)
		img->iso.rot_y += 0.1;
	else if (key == YM_ROT)
		img->iso.rot_y -= 0.1;
	else if (key == XP_ROT)
		img->iso.rot_x += 0.1;
	else
		img->iso.rot_x -= 0.1;
}

void	op_scale(int key, t_data *img)
{
	if (key == ZOOMIN)
		img->iso.scale += 2;
	else
		img->iso.scale -= 2;
}

int	check_keys(int key, t_data *img)
{
	if (key == ESC)
		ft_close(img);
	else if (key == ZOOMIN || key == ZOOMOUT)
		op_scale(key, img);
	else if (key == UP || key == DOWN || key == LEFT
		|| key == RIGHT)
		op_translate(key, img);
	else if (key == ZP_ROT || key == ZM_ROT || key == YP_ROT
		|| key == YM_ROT || key == XP_ROT || key == XM_ROT)
		op_rotate(key, img);
	else if (key == PROJECTION)
		img->proj *= -1;
	else
		return (0);
	return (1);
}

int	deal_key(int key, void *data)
{
	t_data	*img;

	img = (t_data *)data;
	if (!check_keys(key, img))
		return (0);
	mlx_clear_window(img->mlx, img->mlx_win);
	mlx_destroy_image(img->mlx, img->img);
	img->img = mlx_new_image(img->mlx, 1920, 1080);
	if (img->proj == 1)
		draw_file_iso(img);
	else
		draw_file_2d(img);
	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	draw_menu(img);
	return (0);
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
