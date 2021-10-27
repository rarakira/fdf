/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:10:29 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 11:40:47 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	offscreen(int x, int y)
{
	if (x <= 0 || x >= WIN_WIDTH)
		return (1);
	if (y <= 0 || y >= WIN_HEIGHT)
		return (1);
	return (0);
}

void	my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (offscreen(x, y))
		return ;
	dst = fdf->addr + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	map_points(t_point *this, t_fdf *fdf)
{
	double	x_upd;
	double	y_upd;
	t_point	tmp;

	init_tpoint(&tmp, this->x, this->y, this->z);
	x_upd = (tmp.x - tmp.y) * cos(RAD_ANGLE);
	y_upd = -(tmp.z) + (tmp.x + tmp.y) * sin(RAD_ANGLE);
	this->x = (int)round(x_upd) + fdf->camera.x_offset;
	this->y = (int)round(y_upd) + fdf->camera.y_offset;
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
