/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:17:26 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/26 17:23:36 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int find_diff(int a, int b)
{
	int diff;

	diff = a - b;
	if (diff < 0)
		return (diff * -1);
	return (diff);
}

static double	find_incr(int start, int fin)
{
	if (start > fin)
		return (-1.0);
	return (1.0);
}

void	draw_mid_by_y(t_fdf *fdf, t_pair *current,t_point *start, t_point *end)
{
	t_pair	increment;

	increment.y = find_incr(start->y, end->y);
	increment.x = find_incr(start->x, end->x);
	increment.x *= find_diff(start->x, end->x) / (float) find_diff(start->y, end->y);
	while (current->y != end->y)
	{
		current->y += increment.y;
		current->x += increment.x;
		my_mlx_pixel_put(fdf, round(current->x), round(current->y), get_grad_color(start->color, end->color, find_percent(start->y, end->y, round(current->y))));
	}
}

void	draw_mid_by_x(t_fdf *fdf, t_pair *current,t_point *start, t_point *end)
{
	t_pair	increment;

	increment.y = find_incr(start->y, end->y);
	increment.x = find_incr(start->x, end->x);
	increment.y *= find_diff(start->y, end->y) / (float) find_diff(start->x, end->x);
	while (current->x != end->x)
	{
		current->y += increment.y;
		current->x += increment.x;
		my_mlx_pixel_put(fdf, round(current->x), round(current->y), get_grad_color(start->color, end->color, find_percent(start->x, end->x, round(current->x))));
	}
}

void draw_line(t_fdf *fdf, t_point *start, t_point *end)
{
	t_pair	current;
	t_pair	increment;

	current.x = start->x;
	current.y = start->y;
	increment.y = find_incr(start->y, end->y);
	increment.x = find_incr(start->x, end->x);
	my_mlx_pixel_put(fdf, start->x, start->y, start->color);
	if (find_diff(start->x, end->x) < find_diff(start->y, end->y))
		draw_mid_by_y(fdf, &current, start, end);
	else
		draw_mid_by_x(fdf, &current, start, end);
	my_mlx_pixel_put(fdf, end->x, end->y, end->color);
}

/*
void draw_line(t_fdf *fdf, t_point *start, t_point *end)
{
	double	x;
	double	y;
	double	increment_x;
	double	increment_y;

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
	my_mlx_pixel_put(fdf, start->x, start->y, start->color);
	if (diff_x < diff_y)
	{
		increment_x *= diff_x / (float) diff_y;
		while (y != end->y)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(fdf, round(x), round(y), get_grad_color(start->color, end->color, find_percent(start->y, end->y, round(y))));
		}
	}
	else
	{
		increment_y *= diff_y / (float) diff_x;
		while (x != end->x)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(fdf, round(x), round(y), get_grad_color(start->color, end->color, find_percent(start->x, end->x, round(x))));
		}
	}
	my_mlx_pixel_put(fdf, end->x, end->y, end->color);
}
*/