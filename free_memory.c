/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:58:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 09:48:40 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	free_fdf(t_fdf *fdf)
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
	return (1);
}

int	free_points(t_point *list)
{
	t_point	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	return (1);
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
