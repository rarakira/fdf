/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_and_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 10:01:28 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 11:54:11 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	find_percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	if (current == start)
		return (0.0);
	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

static int	get_tint(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_grad_color(int start, int end, double percentage)
{
	int	red;
	int	green;
	int	blue;

	red = get_tint((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	green = get_tint((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	blue = get_tint(start & 0xFF, end & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}
