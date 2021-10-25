/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 11:31:10 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/25 14:58:14 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void x_rotation(t_point *this, double xx)
{
	int	z;
	int y;

	z = this->z;
	y = this->y;
	this->y = (int)(y * cos(xx) + z * sin(xx));
	this->z = (int)(-y * sin(xx) + z * cos(xx));
}