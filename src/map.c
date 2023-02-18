/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvalli-v <fvalli-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:28:06 by fvalli-v          #+#    #+#             */
/*   Updated: 2023/02/18 14:30:41 by fvalli-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	word_count(char	**strs)
{
	int	count;

	count = 0;
	while (strs[count])
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
