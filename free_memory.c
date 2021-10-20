/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:58:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/20 15:27:31 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_fdf(t_fdf *fdf)
{
	int		i;

	i = 0;
	while (i < fdf->map_i.map_h)
	{
		free(fdf->map_i.map[i]);
		free(fdf->map_i.color[i]);
		i++;
	}
	free(fdf->map_i.map);
	free(fdf->map_i.color);
}

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

void	free_arr(int **arr, int depth)
{
	int		i;

	i = 0;
	while (i < depth && arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_if_not_null(void *ptr)
{
	if (ptr)
		free(ptr);
}
