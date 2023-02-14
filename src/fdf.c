/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/14 18:37:14 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_a_line(t_data *img, int x0, int y0, int x1, int y1)
{
	int dx, dy, p, x, y;

	// x0 *= img->zoom;
	// y0 *= img->zoom;
	// x1 *= img->zoom;
	// y1 *= img->zoom;
	x=x0;
	y=y0;
	dx=x1-x0;
	dy=y1-y0;
	p=2*dy-dx;
	if (x0 != x1)
	{
		while(x < x1)
		{
			my_mlx_pixel_put(img, x, y, 0x0000FFFF);
			x++;
			if(p>=0)
			{
				y++;
				p=p+2*dy-2*dx;
			}
			else
				p=p+2*dy;
		}
	}
	else
	{
		while(y < y1)
		{
			my_mlx_pixel_put(img, x, y, 0x0000FFFF);
			y++;
		}
	}
}

t_data	*init_data(void)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1000, 500, "Hello world!");
	data->img = mlx_new_image(data->mlx, 1000, 500);
	data->addr = NULL;
	data->bits_per_pixel = 0;
	data->line_length = 0;
	data->endian = 0;
	data->width_map = 0;
	data->height_map = 0;
	data->map = NULL;
	data->zoom = 10;
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
			draw_a_line(img, x, y, x + 1, y);
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
	static int x = 100, y = 100;

	img = (t_data *)data;
	if (key == ESC)
		ft_close(img);
	else if (key == UP)
	{
		print_line(x, y, img);
		// draw_a_line(img, 100, 100, 200, 200);
		x += 10;
	}
	else
		ft_printf("key pressed = %d\n", key);
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
	// draw_a_line(img, 100, 100, 200, 100);
	// draw_a_line(img, 100, 100, 100, 200); //error printing vertical line. Correct this.

	// mlx_mouse_hook (img->mlx_win, read_mouse, img);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_key_hook(img->mlx_win, deal_key, img);
	mlx_loop(img->mlx);
	free(img);
	return (0);
}
