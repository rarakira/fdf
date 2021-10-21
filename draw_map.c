/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:16:00 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 16:44:58 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char *dst;
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int find_diff(int a, int b)
{
	int diff;

	diff = a - b;
	if (diff < 0)
		return (diff * -1);
	return (diff);
}

void my_draw_line(t_fdf *fdf, int x_start, int y_start, int x_end, int y_end, int color)
{
	double x;
	double y;
	double increment_x;
	double increment_y;

	x = x_start;
	y = y_start;
	increment_y = 1.0;
	if (y_start > y_end)
		increment_y = -1.0;
	increment_x = 1.0;
	if (x_start > x_end)
		increment_x = -1.0;
	int diff_x = find_diff(x_start, x_end);
	int diff_y = find_diff(y_start, y_end);
	my_mlx_pixel_put(fdf, x, y, color);
	if (diff_x < diff_y)
	{
		increment_x *= diff_x / (float) diff_y;
		while (y != y_end)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(fdf, round(x), round(y), color);
		}
	}
	else
	{
		increment_y *= diff_y / (float) diff_x;
		while (x != x_end)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(fdf, round(x), round(y), color);
		}
	}
	my_mlx_pixel_put(fdf, x_end, y_end, color);
}

/*
int	map_point_x(int	y, int x, int z)
{
	//printf("MAP X:\nx = %d, y = %d, z = %d\n", x, y, z);
	//printf("sum = %d\n", x * 1 + y * 1 + z * 0);
	return ((int)((x * 1 + y * 1 + z * 0) * 20));
}

int	map_point_y(int	y, int x, int z)
{
	//printf("MAP Y:\nx = %d, y = %d, z = %d\n", x, y, z);
	//printf("sum = %f\n", (x * (-0.5) + y * 0.5 + z * 1));
	return ((int)((x * (-0.5) + y * 0.5 + z * -1) * 20));
} */

// x_cart = (x - y) * cos(RAD_ANGLE);
int	map_point_x(int	y, int x, int z, t_fdf	*fdf)
{
	double	x_cart;
	(void) z;
	// (void) fdf;

	x_cart = (x + y) * cos(RAD_ANGLE);
	// printf("MAP X:\nx = %d, y = %d, z = %d\n", x, y, z);
	// printf("x_cart = %f\n", x_cart);
	return ((int)(x_cart * fdf->map_i.z_depth) + fdf->camera.x_offset);
}

// y_cart = -z + (x + y) * sin(RAD_ANGLE);
int	map_point_y(int	y, int x, int z, t_fdf	*fdf)
{
	double	y_cart;
	// (void) fdf;

	y_cart = -z + x * -sin(RAD_ANGLE) + y * sin(RAD_ANGLE);
	// printf("MAP Y:\nx = %d, y = %d, z = %d\n", x, y, z);
	// printf("y_cart = %f\n", y_cart);
	return ((int)(y_cart * fdf->map_i.z_depth) + fdf->camera.y_offset);
}

void	fill_background(t_fdf *fdf)
{
	int		x;
	int		y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			my_mlx_pixel_put(fdf, x, y, COL_BLACK);
			x++;
		}
		y++;
	}
}
void	draw_map(t_fdf	*fdf, int	**map)
{
	fill_background(fdf);
	/* Drawing map */
	int		x_start, y_start;
	int		x_fin, y_fin;

	for (int y = 0; y < fdf->map_i.map_h; y++)
	{
		for (int x = 0; x < fdf->map_i.map_w; x++)
		{
			// printf("y = %d, x = %d\n", y, x);
			if (x < (fdf->map_i.map_w - 1)) // draw horizontal
			{
				// printf("point1 %d, point2 %d\n", map[y][x], map[y][x + 1]);
				x_start = map_point_x(x, y, map[y][x], fdf);
				y_start = map_point_y(x, y, map[y][x], fdf);
				x_fin = map_point_x(x + 1, y, map[y][x + 1], fdf);
				y_fin = map_point_y(x + 1, y, map[y][x + 1], fdf);
				// printf("HOR: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", x_start, y_start, x_fin, y_fin);
				my_draw_line(fdf, x_start, y_start, x_fin, y_fin, COL_YELLOW);
			}
			if (y < (fdf->map_i.map_h - 1)) // draw vertical
			{
				// printf("point1 %d, point2 %d\n", map[y][x], map[y+ 1][x]);
				x_start = map_point_x(x, y, map[y][x], fdf);
				y_start = map_point_y(x, y, map[y][x], fdf);
				x_fin = map_point_x(x, y + 1, map[y + 1][x], fdf);
				y_fin = map_point_y(x, y + 1, map[y + 1][x], fdf);
				// printf("VERT: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", x_start, y_start, x_fin, y_fin);
				my_draw_line(fdf, x_start, y_start, x_fin, y_fin, COL_RED);
			}
		}
	}
}