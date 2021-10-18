/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:41:56 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/18 16:33:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"


t_point	*ft_point_new(int z, int x)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (point)
	{
		point->z = z;
		point->x = x;
		point->next = NULL;
	}
	return (point);
}

t_point	*ft_point_last(t_point *lst)
{
	t_point	*tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	add_line_front(t_point **start, t_point *new)
{
	t_point		*tmp;

	tmp = ft_point_last(new);
	if (new)
	{
		new->next = *start;
		*start = new;
	}
}

void	ft_point_add_front(t_point **start, t_point *new)
{
	if (new)
	{
		new->next = *start;
		*start = new;
	}
}

void	ft_point_add_back(t_point **start, t_point *new)
{
	t_point	*tmp;

	if (start)
	{
		if (*start && new)
		{
			tmp = ft_point_last(*start);
			tmp->next = new;
		}
		else
			if (!(*start) && new)
				*start = new;
	}
}

int	parse_line(char *str, t_point *start)
{
	char	**nums;
	t_point	*tmp;
	t_point	*current_line = NULL;
	int		i;

	i = 0;
	nums = ft_split(str, ' ');
	while (nums[i])
		i++;
	while (nums[i])
	{
		tmp = ft_point_new(ft_atoi(nums[i]), i);
		ft_point_add_back(&current_line, tmp);
		free(nums[i]);
		i++;
	}
	free(nums);
	add_line_front(&start, current_line);
	if (start)
	{
		ft_printf("z = %d\n", start->z);
		start = start->next;
	}
	return (i);
}

t_point	**init_map(char	*map_file)
{
	int		fd;
	int		res;
	t_point	**map = NULL;
	t_point	*flat_map = NULL;
	char	*line;
	int		i = 0;
	int		width = 0;

	if (open(map_file, O_DIRECTORY) != -1)
		exit_on_error(ERR_FD_IS_DIR);
	fd = open(map_file, O_RDONLY);
	res = get_next_line(fd, &line);
	while (res != 0 && ++i)
	{
		//if (parse_line(line, flat_map))
		//	exit_on_error(ERR_MAP);
		//else
		//	if (line)
		//		free(line);
		width = parse_line(line, flat_map);
		res = get_next_line(fd, &line);
		ft_printf("width = %d, i = %d\n", width, i);
	}
	ft_printf("width = %d, i = %d\n", width, i);
	if (line)
		free(line);
	while (flat_map)
	{
		ft_printf("z = %d\n", flat_map->z);
	}
	if (fd == -1)
		exit_on_error(ERR_FD_OPEN);
	if (close(fd) == -1)
		exit_on_error(ERR_FD_CLOSE);
	return (map);
}