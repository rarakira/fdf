/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:17:26 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 11:10:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float	find_diff(int a, int b)
{
	float	diff;

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

void	draw_mid_by_y(t_fdf *fdf, t_pair *current, t_point *start, t_point *end)
{
	t_pair	increment;

	increment.y = find_incr(start->y, end->y);
	increment.x = find_incr(start->x, end->x);
	increment.x *= find_diff(start->x, end->x) / find_diff(start->y, end->y);
	while (current->y != end->y)
	{
		current->y += increment.y;
		current->x += increment.x;
		my_mlx_pixel_put(fdf, round(current->x), round(current->y),
			get_grad_color(start->color, end->color,
				find_percent(start->y, end->y, round(current->y))));
	}
}

void	draw_mid_by_x(t_fdf *fdf, t_pair *current, t_point *start, t_point *end)
{
	t_pair	increment;

	increment.y = find_incr(start->y, end->y);
	increment.x = find_incr(start->x, end->x);
	increment.y *= find_diff(start->y, end->y) / find_diff(start->x, end->x);
	while (current->x != end->x)
	{
		current->y += increment.y;
		current->x += increment.x;
		my_mlx_pixel_put(fdf, round(current->x), round(current->y),
			get_grad_color(start->color, end->color,
				find_percent(start->x, end->x, round(current->x))));
	}
}

void	draw_line(t_fdf *fdf, t_point *start, t_point *end)
{
	t_pair	current;

	current.x = start->x;
	current.y = start->y;
	my_mlx_pixel_put(fdf, start->x, start->y, start->color);
	if (find_diff(start->x, end->x) < find_diff(start->y, end->y))
		draw_mid_by_y(fdf, &current, start, end);
	else
		draw_mid_by_x(fdf, &current, start, end);
	my_mlx_pixel_put(fdf, end->x, end->y, end->color);
}
