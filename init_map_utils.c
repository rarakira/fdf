/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:49:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/19 12:35:03 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	*ft_point_new(int x, int y, int z)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (point)
	{
		point->x = x;
		point->y = y;
		point->z = z;
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
		tmp->next = *start;
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
			*start = new;
	}
}