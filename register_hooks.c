/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   register_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:43:10 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/26 12:58:37 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_hook(int keycode, t_fdf *fdf)
{
	(void) fdf;
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126
		|| keycode == 24 || keycode == 27 || keycode == 18 || keycode == 19
		|| keycode == 20 || keycode == 21 || keycode == 22 || keycode == 23)
	{
		if (keycode == 125)
			fdf->camera.y_offset -= 30;
		if (keycode == 126)
			fdf->camera.y_offset += 30;
		if (keycode == 124)
			fdf->camera.x_offset -= 30;
		if (keycode == 123)
			fdf->camera.x_offset += 30;
		if (keycode == 27)
			fdf->map_i.z_depth -= 1;
		if (keycode == 24)
			fdf->map_i.z_depth += 1;
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
		mlx_clear_window(fdf->mlx, fdf->win);
		draw_map(fdf);
		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	}
	else
		ft_printf("Hello from key_hook - [%d]!\n", keycode);
	return (1);
}

int	win_close(int keycode, t_fdf *fdf)
{
	if (keycode == 53)
	{
		mlx_destroy_image(fdf->mlx, fdf->img);
		mlx_destroy_window(fdf->mlx, fdf->win);
		free_fdf(fdf);
		ft_printf("You pressed ESC. Exiting program, bye!\n");
		//getchar();
		exit (1);
	}
	return (0);
}

int	win_close_x(t_fdf *fdf)
{
	mlx_destroy_image(fdf->mlx, fdf->img);
	mlx_destroy_window(fdf->mlx, fdf->win);
	free_fdf(fdf);
	ft_printf("You clicked [x] button. Exiting program, bye!\n");
	//getchar();
	exit (1);
	return (0);
}

int	mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	(void) fdf;
	ft_printf("Mouse (button = %d) pressed - (%d, %d) !\n", button, x, y);
	return (1);
}

void	register_hooks(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_hook, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, win_close, fdf);
	mlx_hook(fdf->win, 17, 1L << 17, win_close_x, fdf);
	mlx_mouse_hook(fdf->win, mouse_hook, fdf);
}
