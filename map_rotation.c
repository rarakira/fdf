/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:31:10 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/26 09:44:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	x_rotation(t_point *this, double xx)
{
	int	y;
	int	z;

	y = this->y;
	z = this->z;
	this->y = (int)(y * cos(xx) + z * sin(xx));
	this->z = (int)(-y * sin(xx) + z * cos(xx));
}

static void	y_rotation(t_point *this, double yy)
{
	int	x;
	int	z;

	x = this->x;
	z = this->z;
	this->x = (int)(x * cos(yy) + z * sin(yy));
	this->z = (int)(-x * sin(yy) + z * cos(yy));
}

static void	z_rotation(t_point *this, double zz)
{
	int	x;
	int	y;

	x = this->x;
	y = this->y;
	this->x = (int)(x * cos(zz) - y * sin(zz));
	this->y = (int)(x * sin(zz) + y * cos(zz));
}

void	rotate_point(t_point *this, t_fdf *fdf)
{
	if (fdf->camera.zz)
		z_rotation(this, fdf->camera.zz);
	if (fdf->camera.xx)
		x_rotation(this, fdf->camera.xx);
	if (fdf->camera.yy)
		y_rotation(this, fdf->camera.yy);
}
