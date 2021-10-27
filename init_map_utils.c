/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:49:06 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 11:38:40 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

/*
** Calculate colors based on height (z) for each point on map.
*/
void	update_colors(t_fdf *fdf)
{
	int	i;
	int	j;

	i = 0;
	while (i < fdf->map_i.map_h)
	{
		j = 0;
		while (j < fdf->map_i.map_w)
		{
			fdf->map_i.color[i][j] = get_grad_color(COL_RED, COL_YELLOW,
					find_percent(fdf->map_i.z_min,
						fdf->map_i.z_max,
						fdf->map_i.map[i][j]));
			j++;
		}
		i++;
	}
}

/*
** Allocate memory and copy color-value to the color-array.
*/
void	color_to_arr(t_point *flat_map, t_fdf *fdf)
{
	t_point		*tmp;
	int			x;
	int			y;

	y = fdf->map_i.map_h - 1;
	tmp = flat_map;
	while (y >= 0)
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
			fdf->map_i.color[y][x] = tmp->color;
			tmp = tmp->next;
			x++;
		}
		y--;
	}
}

void	check_min_max(t_fdf *fdf, int z, int first)
{
	if (first)
	{
		fdf->map_i.z_min = z;
		fdf->map_i.z_max = z;
	}
	if (fdf->map_i.z_min > z)
		fdf->map_i.z_min = z;
	if (fdf->map_i.z_max < z)
		fdf->map_i.z_max = z;
}

/*
** Allocate memory and copy z-value to the map-array.
*/
void	map_to_arr(t_point *flat_map, t_fdf *fdf)
{
	t_point		*tmp;
	int			x;
	int			y;

	y = fdf->map_i.map_h - 1;
	tmp = flat_map;
	check_min_max(fdf, tmp->z, 1);
	while (y >= 0)
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
			check_min_max(fdf, tmp->z, 0);
			fdf->map_i.map[y][x++] = tmp->z;
			tmp = tmp->next;
		}
		y--;
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
