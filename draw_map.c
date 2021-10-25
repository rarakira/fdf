/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:16:00 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/25 14:53:32 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	offscreen(int x, int y)
{
	if (x <= 0 || x >= WIN_WIDTH)
		return (1);
	if (y <= 0 || y >= WIN_HEIGHT)
		return (1);
	//ft_printf("x = %d, y = %d\n", x, y);
	return (0);
}

void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char *dst;
	// if (offscreen(x, y))
	// 	return ;
	//ft_printf("pixel_put 1 : %d x %d \n", x, y);
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
	//ft_printf("pixel_put 3 \n");
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

	// if (offscreen(x_start, y_start) && offscreen(x_end, y_end))
	// 	return ; // gives cool dissapearing effect
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
	if (!offscreen(round(x), round(y)))
		my_mlx_pixel_put(fdf, x, y, color);
	if (diff_x < diff_y)
	{
		increment_x *= diff_x / (float) diff_y;
		while (y != y_end)
		{
			y += increment_y;
			x += increment_x;
			if (!offscreen(round(x), round(y)))
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
			if (!offscreen(round(x), round(y)))
				my_mlx_pixel_put(fdf, round(x), round(y), color);
		}
	}
	if (!offscreen(round(x), round(y)))
		my_mlx_pixel_put(fdf, x_end, y_end, color);
}

void draw_line(t_fdf *fdf, t_point *start, t_point *end)
{
	double	x;
	double	y;
	double	increment_x;
	double	increment_y;
	int		color = start->color;

	// if (offscreen(x_start, y_start) && offscreen(x_end, y_end))
	// 	return ; // gives cool dissapearing effect
	//printf("DRAW: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start->x, start->y, end->x, end->y);
	x = start->x;
	y = start->y;
	increment_y = 1.0;
	if (start->y > end->y)
		increment_y = -1.0;
	increment_x = 1.0;
	if (start->x > end->x)
		increment_x = -1.0;
	int diff_x = find_diff(start->x, end->x);
	int diff_y = find_diff(start->y, end->y);
	if (!offscreen(start->x, start->y))
		my_mlx_pixel_put(fdf, start->x, start->y, color);
	if (diff_x < diff_y)
	{
		increment_x *= diff_x / (float) diff_y;
		while (y != end->y)
		{
			y += increment_y;
			x += increment_x;
			if (!offscreen(round(x), round(y)))
				my_mlx_pixel_put(fdf, round(x), round(y), color);
		}
	}
	else
	{
		increment_y *= diff_y / (float) diff_x;
		while (x != end->x)
		{
			y += increment_y;
			x += increment_x;
			if (!offscreen(round(x), round(y)))
				my_mlx_pixel_put(fdf, round(x), round(y), color);
		}
	}
	if (!offscreen(end->x, end->y))
		my_mlx_pixel_put(fdf, end->x, end->y, color);
}

/*
int	map_point_x(t_point *this, t_fdf *fdf)
{
	double	x_cart;

	ft_printf("x = %d, y = %d, z = %d\n", this->x, this->y, this->z);
	x_cart = (this->x - this->y) * cos(RAD_ANGLE);
	ft_printf("x_cart = %f\n", x_cart);
	return ((int)(x_cart * fdf->map_i.z_depth) + fdf->camera.x_offset);
}

int	map_point_y(t_point *this, t_fdf *fdf)
{
	double	y_cart;

	ft_printf("x = %d, y = %d, z = %d\n", this->x, this->y, this->z);
	y_cart = -this->z + (this->x + this->y) * sin(RAD_ANGLE);
	ft_printf("y_cart = %f\n", y_cart);
	return ((int)(y_cart * fdf->map_i.z_depth) + fdf->camera.y_offset);
} */


int	map_point_x(int x, int y, t_fdf *fdf)
{
	double	x_cart;

	x_cart = (x - y) * cos(RAD_ANGLE);
	return ((int)(x_cart * fdf->map_i.z_depth) + fdf->camera.x_offset);
}

int	map_point_y(int x, int y, t_fdf *fdf)
{
	double	y_cart;

	y_cart = -(fdf->map_i.map[y][x]) + (x + y) * sin(RAD_ANGLE);
	return ((int)(y_cart * fdf->map_i.z_depth) + fdf->camera.y_offset);
}

void map_points(t_point *this, t_fdf *fdf)
{
	double	x_cart;
	double	y_cart;
	t_point	tmp;

	tmp.x = this->x;
	tmp.y = this->y;
	tmp.z = this->z;
	x_cart = (tmp.x - tmp.y) * cos(RAD_ANGLE);
	y_cart = -(tmp.z) + (tmp.x + tmp.y) * sin(RAD_ANGLE);
	this->x = (int)(x_cart * fdf->map_i.z_depth) + fdf->camera.x_offset;
	this->y = (int)(y_cart * fdf->map_i.z_depth) + fdf->camera.y_offset;
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
	t_point		start;
	t_point		fin;

	for (int y = 0; y < fdf->map_i.map_h; y++)
	{
		for (int x = 0; x < fdf->map_i.map_w; x++)
		{
			if (x < (fdf->map_i.map_w - 1)) // draw horizontal
			{
				start.x = x;
				start.y = y;
				start.z = map[y][x];
				fin.x = x + 1;
				fin.y = y;
				fin.z = map[y][x + 1];
				fin.color = fdf->map_i.color[y][x + 1];
				//if (start.color == -1)
				start.color = COL_YELLOW;
				if (fin.color == -1)
					fin.color = COL_YELLOW;
				x_rotation(&start, fdf->camera.xx);
				x_rotation(&fin, fdf->camera.xx);
				map_points(&start, fdf);
				map_points(&fin, fdf);
				printf("HOR: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				draw_line(fdf, &start, &fin);
			}
			if (y < (fdf->map_i.map_h - 1)) // draw vertical
			{
				start.x = x;
				start.y = y;
				start.z = map[y][x];
				fin.x = x;
				fin.y = y + 1;
				fin.z = map[y + 1][x];
				start.color = fdf->map_i.color[y + 1][x];
				//if (start.color == -1)
				start.color = COL_RED;
				if (fin.color == -1)
					fin.color = COL_RED;
				x_rotation(&start, fdf->camera.xx);
				x_rotation(&fin, fdf->camera.xx);
				map_points(&start, fdf);
				map_points(&fin, fdf);
				printf("VERT: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				draw_line(fdf, &start, &fin);
			}
		}
	}
}

/*
void	draw_map(t_fdf	*fdf, int	**map)
{
	fill_background(fdf);
	t_point		start;
	t_point		fin;

	for (int y = 0; y < fdf->map_i.map_h; y++)
	{
		for (int x = 0; x < fdf->map_i.map_w; x++)
		{
			printf("\e[1;48;5;210;38;5;203my = %d, x = %d\e[0m\n", y, x);
			//start.color = fdf->map_i.color[y][x];
			if (x < (fdf->map_i.map_w - 1)) // draw horizontal
			{
				start.y = y;
				start.x = x;
				start.z = map[y][x];
				fin.x = x + 1;
				fin.y = y;
				fin.z = map[y][x + 1];
				fin.color = fdf->map_i.color[y][x + 1];
				//if (start.color == -1)
				start.color = COL_YELLOW;
				if (fin.color == -1)
					fin.color = COL_YELLOW;
				printf("HOR: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				//x_rotation(&start, fdf->camera.xx);
				//x_rotation(&fin, fdf->camera.xx);
				start.x = map_point_x(&start, fdf);
				start.y = map_point_y(&start, fdf);
				fin.x = map_point_x(&fin, fdf);
				fin.y = map_point_y(&fin, fdf);
				printf("RES: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				draw_line(fdf, &start, &fin);
			}
			if (y < (fdf->map_i.map_h - 1)) // draw vertical
			{
				start.y = y;
				start.x = x;
				start.z = map[y][x];
				fin.x = x;
				fin.y = y + 1;
				fin.z = map[y + 1][x];
				start.color = fdf->map_i.color[y + 1][x];
				//if (start.color == -1)
				start.color = COL_RED;
				if (fin.color == -1)
					fin.color = COL_RED;
				printf("VERT: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				//x_rotation(&start, fdf->camera.xx);
				//x_rotation(&fin, fdf->camera.xx);
				start.x = map_point_x(&start, fdf);
				start.y = map_point_y(&start, fdf);
				fin.x = map_point_x(&fin, fdf);
				fin.y = map_point_y(&fin, fdf);
				printf("RES: x_start = %d, y_start = %d, x_fin = %d, y_fin = %d\n", start.x, start.y, fin.x, fin.y);
				draw_line(fdf, &start, &fin);
			}
		}
	}
}
*/