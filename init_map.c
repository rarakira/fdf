/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:41:56 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/19 15:11:16 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

void	free_points(t_point *list)
{
	t_point	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

int	parse_line(char *str, t_point **start, int	x)
{
	char	**nums;
	t_point	*tmp;
	t_point	*current_line = NULL;
	int		i;

	i = 0;
	nums = ft_split(str, ' ');
	while (nums[i])
	{
		tmp = ft_point_new(x, i, ft_atoi(nums[i]));
		ft_point_add_back(&current_line, tmp);
		free(nums[i]);
		i++;
	}
	free(nums);
	add_line_front(start, current_line);
	return (i);
}

t_point	*read_map(int fd, t_map *map_info)
{
	int		res;
	t_point	*flat_map = NULL;
	char	*line;
	int		h = 0;
	int		width = 0;

	res = get_next_line(fd, &line);
	while (res != 0 && ++h)
	{
		if (res == -1) // ?
			exit_on_error(ERR_MAP);
		width = parse_line(line, &flat_map, h);
		if (width == -1)
		{
			free_points(flat_map);
			if (line)
				free(line);
			exit_on_error(ERR_MAP);
		}
		free(line);
		if (h == 1)
			map_info->map_w = width;
		else
			if (width != map_info->map_w)
			{
				free_points(flat_map);
				return (NULL);
			}
		res = get_next_line(fd, &line);
	}
	if (line)
		free(line);
	map_info->map_h = h;
	if (!map_info->map_h || !map_info->map_w)
		exit_on_error(ERR_MAP);
	return (flat_map);
}

void	consolelog_map(int **map, int width, int height)
{
	int			x;
	int			y;

	y = 0;
	while (y < height)
	{
		x = 0;
		ft_printf("%-6d::\t", y);
		while (x < width)
			ft_printf("%d\t", map[y][x++]);
		ft_printf("\n");
		y++;
	}
	ft_printf("Printed map: %d x %d size\n", width, height);
}

int		map_to_arr(t_point *flat_map, t_fdf *fdf)
{
	t_point		*tmp;
	int			x;
	int			y;

	y = 0;
	tmp = flat_map;
	if (!flat_map) // Could this be an issue?
		return (-1);
	fdf->map_info.map = (int **)malloc(sizeof(int *) * fdf->map_info.map_h);
	fdf->map_info.color = (int **)malloc(sizeof(int *) * fdf->map_info.map_h);
	if (!fdf->map_info.map || !fdf->map_info.color)
	{
		free_points(flat_map);
		exit_on_error(ERR_MEM);
	}
	while (y < fdf->map_info.map_h)
	{
		x = 0;
		fdf->map_info.map[y] = (int *)malloc(sizeof(int) * fdf->map_info.map_w);
		fdf->map_info.color[y] = (int *)malloc(sizeof(int) * fdf->map_info.map_w);
		if (!fdf->map_info.map[y] || !fdf->map_info.color[y])
		{
			free_points(flat_map);
			//free_arr(fdf->map_info.map, y) & free_arr(fdf->map_info.color, y)
			exit_on_error(ERR_MEM);
		}
		while (x < fdf->map_info.map_w && tmp)
		{
			fdf->map_info.map[y][x] = tmp->z;
			fdf->map_info.color[y][x] = tmp->color;
			tmp = tmp->next;
			x++;
		}
		y++;
	}
	consolelog_map(fdf->map_info.map, fdf->map_info.map_w, fdf->map_info.map_h);
	return (1);
}

void	init_map(char	*map_file, t_fdf *fdf)
{
	int		fd;
	t_point	*flat_map;

	flat_map = NULL;
	if (open(map_file, O_DIRECTORY) != -1)
		exit_on_error(ERR_FD_IS_DIR);
	fd = open(map_file, O_RDONLY);
	if (fd == -1)
		exit_on_error(ERR_FD_OPEN);
	flat_map = read_map(fd, &fdf->map_info);
	if (close(fd) == -1)
		exit_on_error(ERR_FD_CLOSE);
	if (!flat_map)
		exit_on_error(ERR_LINE_W);
	if (map_to_arr(flat_map, fdf) == -1)
		exit_on_error(ERR_READING); // think later
	free_points(flat_map);
}