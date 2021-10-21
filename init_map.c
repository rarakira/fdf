/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:41:56 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 09:22:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

static void	free_and_exit(char *str, t_point *current_line, t_point *start)
{
	free(str);
	free_points(current_line);
	free_points(start);
	exit_on_error(ERR_MEM);
}

/*
** Parse and free line, return number of points created.
*/
int	parse_line(char **str, t_point **start)
{
	char	**nums;
	t_point	*tmp;
	t_point	*current_line;
	int		i;

	i = 0;
	tmp = NULL;
	current_line = NULL;
	nums = ft_split(*str, ' ');
	while (nums && nums[i])
	{
		tmp = ft_point_new(nums[i]);
		if (!tmp)
			break ;
		ft_point_add_back(&current_line, tmp);
		i++;
	}
	ft_split_free(nums);
	if (!tmp)
		free_and_exit(*str, current_line, *start);
	add_line_front(start, current_line);
	free(*str);
	*str = NULL;
	return (i);
}

/*
** Read file, create and return ordered t_point structure of all map values.
*/
t_point	*read_map(int fd, t_map *map_i)
{
	int		res;
	t_point	*flat_map;
	char	*line;
	int		width;

	map_i->map_h = 0;
	width = 0;
	flat_map = NULL;
	line = NULL;
	res = get_next_line(fd, &line);
	while (res != 0 && ++map_i->map_h)
	{
		if (res == -1 && free_points(flat_map))
			exit_on_error(ERR_MEM);
		width = parse_line(&line, &flat_map);
		if (map_i->map_h == 1)
			map_i->map_w = width;
		if (map_i->map_h != 1 && width != map_i->map_w && free_points(flat_map))
			return (NULL);
		res = get_next_line(fd, &line);
	}
	free(line);
	return (flat_map);
}

/*
** Check file permissions, malloc map array inside the structure.
*/
void	init_map(char	*map_file, t_fdf *fdf)
{
	int		fd;
	t_point	*flat_map;

	flat_map = NULL;
	if (open(map_file, O_DIRECTORY) != -1) // if DIR - exit
		exit_on_error(ERR_FD_IS_DIR);
	fd = open(map_file, O_RDONLY);
	if (fd == -1) // if troubles opening FD - exit
		exit_on_error(ERR_FD_OPEN);
	flat_map = read_map(fd, &fdf->map_i);
	if (close(fd) == -1) // if troubles closing FD - exit
		exit_on_error(ERR_FD_CLOSE);
	if (!flat_map) // if bad width of lines - exit
		exit_on_error(ERR_LINE_W);
	list_to_arr(flat_map, fdf);
	free_points(flat_map);
}
