/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:49:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 09:02:22 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

/*
** Allocate memory and copy color-value to the color-array.
*/
void	color_to_arr(t_point *flat_map, t_fdf *fdf)
{
	t_point		*tmp;
	int			x;
	int			y;

	y = 0;
	tmp = flat_map;
	while (y < fdf->map_i.map_h)
	{
		x = 0;
		fdf->map_i.color[y] = (int *)malloc(sizeof(int) * fdf->map_i.map_w);
		if (!fdf->map_i.color[y])
		{
			free_points(flat_map);
			free_arr(fdf->map_i.map, fdf->map_i.map_h);
			free_arr(fdf->map_i.color, fdf->map_i.map_h);
			exit_on_error(ERR_MEM);
		}
		while (x < fdf->map_i.map_w && tmp)
		{
			fdf->map_i.color[y][x] = tmp->z;
			tmp = tmp->next;
			x++;
		}
		y++;
	}
}

/*
** Allocate memory and copy z-value to the map-array.
*/
void	map_to_arr(t_point *flat_map, t_fdf *fdf)
{
	t_point		*tmp;
	int			x;
	int			y;

	y = 0;
	tmp = flat_map;
	while (y < fdf->map_i.map_h)
	{
		x = 0;
		fdf->map_i.map[y] = (int *)malloc(sizeof(int) * fdf->map_i.map_w);
		if (!fdf->map_i.map[y])
		{
			free_points(flat_map);
			free_arr(fdf->map_i.map, fdf->map_i.map_h);
			exit_on_error(ERR_MEM);
		}
		while (x < fdf->map_i.map_w && tmp)
		{
			fdf->map_i.map[y][x] = tmp->z;
			tmp = tmp->next;
			x++;
		}
		y++;
	}
}

/*
** Convert t_point list to int-matrix inside fdf-structure.
*/
void	list_to_arr(t_point *flat_map, t_fdf *fdf)
{
	fdf->map_i.map = (int **)malloc(sizeof(int *) * fdf->map_i.map_h);
	fdf->map_i.color = (int **)malloc(sizeof(int *) * fdf->map_i.map_h);
	if (!fdf->map_i.map || !fdf->map_i.color)
	{
		free(fdf->map_i.map);
		free(fdf->map_i.color);
		free_points(flat_map);
		exit_on_error(ERR_MEM);
	}
	map_to_arr(flat_map, fdf);
	color_to_arr(flat_map, fdf);
}
