/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 10:25:59 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/05 10:05:48 by fvalli-v         ###   ########.fr       */
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
	dx=x1-x0;
	dy=y1-y0;

	x=x0;
	y=y0;

	p=2*dy-dx;

	while(x<x1)
	{
		if(p>=0)
		{
			my_mlx_pixel_put(img, x, y, 0x0000FFFF);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			my_mlx_pixel_put(img, x, y, 0x0000FFFF);
			p=p+2*dy;
		}
		x=x+1;
	}
	// while (x1 <= x2)
	// {
	// 	my_mlx_pixel_put(img, x1, (m * x1 + c), 0x0000FFFF);

	// 	x1++;
	// }
}

void bresenham_line(t_data *img, int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int x, y, p;

    if (dx >= dy) {
        if (x1 > x2) {
            int t = x1; x1 = x2; x2 = t;
            t = y1; y1 = y2; y2 = t;
        }
        x = x1; y = y1;
        my_mlx_pixel_put(img, x, y, 0x0000FFFF);
        p = 2 * dy - dx;
        while (x < x2) {
            x = x + 1;
            if (p < 0) {
                p = p + 2 * dy;
            } else {
                y = y + 1;
                p = p + 2 * (dy - dx);
            }
            my_mlx_pixel_put(img, x, y, 0x0000FFFF);
        }
    } else {
        if (y1 > y2) {
            int t = x1; x1 = x2; x2 = t;
            t = y1; y1 = y2; y2 = t;
        }
        x = x1; y = y1;
        my_mlx_pixel_put(img, x, y, 0x0000FFFF);
        p = 2 * dx - dy;
        while (y < y2) {
            y = y + 1;
            if (p < 0) {
                p = p + 2 * dx;
            } else {
                x = x + 1;
                p = p + 2 * (dx - dy);
            }
            my_mlx_pixel_put(img, x, y, 0x0000FFFF);
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
	// ft_printf("height = %d | width = %d \n", img->height_map, img->width_map);
	while (i < img->height_map)
	{
		str = get_next_line(fd);
		strs = ft_split(str, ' ');
		map[i] = (int *)malloc(sizeof(int) * img->width_map);
		// ft_printf("i = %d | j = %d | height = %d | width = %d \n",i, j, img->height_map, img->width_map);
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
	img->map = map;
	close(fd);
}

void	print_map(t_data *img)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	// ft_printf("height = %d | width = %d \n", img->height_map, img->width_map);
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

int	ft_close(int keycode, t_data *vars)
{
	(void)keycode;
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	return (0);
}

int	main(int argc , char **argv)
{
	t_data	*img;

	img = init_data();
		/*
	** After creating an image, we can call `mlx_get_data_addr`, we pass
	** `bits_per_pixel`, `line_length`, and `endian` by reference. These will
	** then be set accordingly for the *current* data address.
	*/
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




	bresenham_line(img, 200, 300, 300, 10);

	bresenham_line(img, 300, 10, 200, 300);

	bresenham_line(img, 200, 200, 300, 10);

	bresenham_line(img, 100, 100, 300, 10);


	// while (i < 50)
	// {
	// 	while (j < 50)
	// 	{
	// 		color = color + 1000;
	// 		my_mlx_pixel_put(&img, j, i, color);

	// 		j++;
	// 	}
	// 	i++;
	// 	j = 10;
	// 	color = 0x0000FFFF;
	// }

	mlx_put_image_to_window(img->mlx, img->mlx_win, img->img, 0, 0);
	// ft_printf("bpp = %d | line_length = %d | endian = %d \n", img.bits_per_pixel, img.line_length, img.endian);
	// mlx_hook(img->mlx_win, 2, 1L<<0, ft_close, img);
	mlx_hook(img->mlx_win, 17, 0, ft_close, img);
	mlx_loop(img->mlx);

	//Remember to free t_data
}
