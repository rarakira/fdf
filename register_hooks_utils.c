/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 12:55:04 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 13:58:08 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate_map(int keycode, t_fdf *fdf)
{
	if (keycode == 125)
		fdf->camera.y_offset -= 30;
	if (keycode == 126)
		fdf->camera.y_offset += 30;
	if (keycode == 124)
		fdf->camera.x_offset -= 30;
	if (keycode == 123)
		fdf->camera.x_offset += 30;
}

static void	zoom_in_out(int keycode, t_fdf *fdf)
{
	if (keycode == 27 && fdf->map_i.z_depth > 0)
		fdf->map_i.z_depth -= 1;
	if (keycode == 24)
		fdf->map_i.z_depth += 1;
}

static void	rotate_map(int keycode, t_fdf *fdf)
{
	if (keycode == 18)
		fdf->camera.xx -= 0.2;
	if (keycode == 19)
		fdf->camera.xx += 0.2;
	if (keycode == 20)
		fdf->camera.yy -= 0.2;
	if (keycode == 21)
		fdf->camera.yy += 0.2;
	if (keycode == 22)
		fdf->camera.zz -= 0.2;
	if (keycode == 23)
		fdf->camera.zz += 0.2;
}

static void	projection(int keycode, t_fdf *fdf)
{
	if (keycode == 1)
		fdf->camera.iso = 0;
	if (keycode == 34)
		fdf->camera.iso = 1;
	if (keycode == 17)
		fdf->camera.iso = 2;
	fdf->camera.xx = 0.0;
	fdf->camera.yy = 0.0;
	fdf->camera.zz = 0.0;
}

int	key_hook(int keycode, t_fdf *fdf)
{
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
		translate_map(keycode, fdf);
	else if (keycode == 24 || keycode == 27)
		zoom_in_out(keycode, fdf);
	else if (keycode == 18 || keycode == 19 || keycode == 20
		|| keycode == 21 || keycode == 22 || keycode == 23)
		rotate_map(keycode, fdf);
	else if (keycode == 17 || keycode == 34 || keycode == 1)
		projection(keycode, fdf);
	else
	{
		ft_printf("Hello from key_hook - [%d]!\n", keycode);
		return (0);
	}
	mlx_clear_window(fdf->mlx, fdf->win);
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (1);
}
