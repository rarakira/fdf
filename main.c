/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 16:42:02 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

void	init_mlx(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx && free_fdf(fdf))
		exit_on_error(ERR_MLX);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	if (!fdf->win && free_fdf(fdf))
		exit_on_error(ERR_WIN);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img && free_fdf(fdf))
		exit_on_error(ERR_IMG);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
}

void	init_fdf(t_fdf *fdf)
{
	fdf->map_i.z_depth = 5;
	fdf->map_i.map_h = 0;
	fdf->camera.zoom = 1.0;
	fdf->camera.x_offset = 400;
	fdf->camera.y_offset = 300;
	fdf->camera.xx = 0.0;
	fdf->camera.yy = 0.0;
	fdf->camera.zz = 0.0;
	ft_printf("FDF init: All good\n");
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc == 2)
	{
		init_fdf(&fdf);
		init_map(argv[1], &fdf);
		init_mlx(&fdf);
		//init_camera(&fdf);
		register_hooks(&fdf);
		draw_map(&fdf, fdf.map_i.map);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		ft_printf("Bpp: %d, win_w = %d, win_h = %d line_len = %d\n", fdf.bits_per_pixel, WIN_WIDTH, WIN_HEIGHT, fdf.line_length);
		mlx_loop(fdf.mlx);
	}
	exit_on_error(ERR_ARGS);
	return (0);
}

/*
void	init_camera(t_fdf *fdf)
{
	int	width;
	int	height;
	int	y_top;
	int	y_bottom;
	int depth_h;
	int depth_w;

	width = (fdf->map_i.map_h + fdf->map_i.map_w); // / 2
	if (fdf->map_i.z_min < 0 && fdf->map_i.z_max < 0)
		height = fdf->map_i.z_min - fdf->map_i.z_max;
	else // if (fdf->map_i.z_min < 0)
		height = fdf->map_i.z_max - fdf->map_i.z_min;
	y_top = map_point_y(0, 0, fdf->map_i.map[0][0], fdf);
	y_bottom = map_point_y(fdf->map_i.map_h - 1, fdf->map_i.map_w - 1, fdf->map_i.map[fdf->map_i.map_h - 1][fdf->map_i.map_w - 1], fdf);
	height += find_diff(y_top, y_bottom);
	depth_h = IMG_HEIGHT / height;
	depth_w = IMG_WIDTH / width;
	if (depth_h < depth_w)
		fdf->map_i.z_depth = depth_w;
	else
		fdf->map_i.z_depth = depth_h;
	fdf->camera.x_offset = WIN_WIDTH / 2;
	fdf->camera.y_offset = WIN_HEIGHT / 2;
	ft_printf("CAMERA init: All good\n");
	ft_printf("y_top x y_bottom :: %d x %d\n", y_top, y_bottom);
	ft_printf("Height x Width :: %d x %d\n", height, width);
	ft_printf("d-Height x d-Width :: %d x %d\n", depth_h, depth_w);
	ft_printf("z_min x z-max :: %d x %d\n", fdf->map_i.z_min, fdf->map_i.z_max);
	ft_printf("fin_depth = %d\n", fdf->map_i.z_depth);
	ft_printf("MAP SIZE :: %d x %d\n", fdf->map_i.map_h, fdf->map_i.map_w);
}
*/