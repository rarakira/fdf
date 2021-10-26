/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:16:00 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/26 14:10:17 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_horizontal_line(int x, int y, t_fdf *fdf)
{
	t_point		start;
	t_point		fin;

	start.x = (x - fdf->map_i.map_w / 2) * fdf->map_i.z_depth;
	start.y = (y - fdf->map_i.map_h / 2) * fdf->map_i.z_depth;
	start.z = fdf->map_i.map[y][x] * fdf->map_i.z_depth;
	fin.x = ((x + 1) - fdf->map_i.map_w / 2) * fdf->map_i.z_depth;
	fin.y = (y - fdf->map_i.map_h / 2) * fdf->map_i.z_depth;
	fin.z = fdf->map_i.map[y][x + 1] * fdf->map_i.z_depth;
	start.color = fdf->map_i.color[y][x];
	fin.color = fdf->map_i.color[y][x + 1];
	if (start.color == -1)
		start.color = COL_VIOLET;
	if (fin.color == -1)
		fin.color = COL_VIOLET;
	rotate_point(&start, fdf);
	rotate_point(&fin, fdf);
	map_points(&start, fdf);
	map_points(&fin, fdf);
	draw_line(fdf, &start, &fin);
}

void	draw_vertical_line(int x, int y, t_fdf *fdf)
{
	t_point		start;
	t_point		fin;

	init_tpoint(&start,
		(x - fdf->map_i.map_w / 2) * fdf->map_i.z_depth,
		(y - fdf->map_i.map_h / 2) * fdf->map_i.z_depth,
		fdf->map_i.map[y][x] * fdf->map_i.z_depth);
	init_tpoint(&fin,
		(x - fdf->map_i.map_w / 2) * fdf->map_i.z_depth,
		((y + 1) - fdf->map_i.map_h / 2) * fdf->map_i.z_depth,
		fdf->map_i.map[y + 1][x] * fdf->map_i.z_depth);
	start.color = fdf->map_i.color[y][x];
	fin.color = fdf->map_i.color[y + 1][x];
	if (start.color == -1)
		start.color = COL_VIOLET;
	if (fin.color == -1)
		fin.color = COL_VIOLET;
	rotate_point(&start, fdf);
	rotate_point(&fin, fdf);
	map_points(&start, fdf);
	map_points(&fin, fdf);
	draw_line(fdf, &start, &fin);
}

static void	print_in_order(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map_i.map_h)
	{
		x = 0;
		while (x < fdf->map_i.map_w)
		{
			if (x < (fdf->map_i.map_w - 1))
				draw_horizontal_line(x, y, fdf);
			if (y < (fdf->map_i.map_h - 1))
				draw_vertical_line(x, y, fdf);
			x++;
		}
		y++;
	}
}

static void	print_backwards(t_fdf *fdf)
{
	int	x;
	int	y;

	y = fdf->map_i.map_h - 1;
	while (y >= 0)
	{
		x = fdf->map_i.map_w - 1;
		while (x >= 0)
		{
			if (x < (fdf->map_i.map_w - 1))
				draw_horizontal_line(x, y, fdf);
			if (y < (fdf->map_i.map_h - 1))
				draw_vertical_line(x, y, fdf);
			x--;
		}
		y--;
	}
}

void	draw_map(t_fdf *fdf)
{
	t_point		start;
	t_point		fin;

	fill_background(fdf);
	init_tpoint(&start, 0, 0, 0);
	init_tpoint(&fin, 0, fdf->map_i.map_h - 1, 0);
	rotate_point(&start, fdf);
	rotate_point(&fin, fdf);
	map_points(&start, fdf);
	map_points(&fin, fdf);
	//ft_printf("start %d, fin %d\n", start.y, fin.y);
	if (start.y < fin.y)
		print_in_order(fdf);
	else
		print_backwards(fdf);
}