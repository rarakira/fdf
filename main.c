/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/22 13:49:23 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

void	init_mlx(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx && free_fdf(fdf))
		exit_on_error(ERR_MLX);
	ft_printf("MLX init: All good\n");
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	if (!fdf->win && free_fdf(fdf))
		exit_on_error(ERR_WIN);
	ft_printf("WIN init: All good\n");
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img && free_fdf(fdf))
		exit_on_error(ERR_IMG);
	ft_printf("IMG init: All good\n");
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
	ft_printf("ADDR init: All good\n");
}

void	init_fdf(t_fdf *fdf)
{
	fdf->map_i.z_depth = 15;
	fdf->map_i.map_h = 0;
	fdf->camera.zoom = 1.0;
	fdf->camera.x_offset = 400;
	fdf->camera.y_offset = 300;
	fdf->camera.xx = 0.0;
	fdf->camera.yy = 0.0;
	fdf->camera.zz = 0.0;
	ft_printf("FDF init: All good\n");
}

void	init_camera(t_fdf *fdf)
{
	int	width;
	int	height;
	int	y_top;
	int	y_bottom;
	int depth_h;
	int depth_w;

	ft_printf("right_pt = %d, left_pt = %d\n", map_point_x(0, fdf->map_i.map_w - 1, fdf->map_i.map[0][fdf->map_i.map_w - 1], fdf), map_point_x(fdf->map_i.map_h - 1, 0, fdf->map_i.map[fdf->map_i.map_h - 1][0], fdf));
	width = map_point_x(0, fdf->map_i.map_w - 1, fdf->map_i.map[0][fdf->map_i.map_w - 1], fdf)
		- map_point_x(fdf->map_i.map_h - 1, 0, fdf->map_i.map[fdf->map_i.map_h - 1][0], fdf); // / 2
	ft_printf("Width :: %d \n", width);
	ft_printf("z_min x z-max :: %d x %d\n", fdf->map_i.z_min, fdf->map_i.z_max);
	if (fdf->map_i.z_min < 0 && fdf->map_i.z_max < 0)
		height = fdf->map_i.z_min - fdf->map_i.z_max;
	else // if (fdf->map_i.z_min < 0)
		height = fdf->map_i.z_max - fdf->map_i.z_min;
	//ft_printf("MAP SIZE :: %d x %d\n", fdf->map_i.map_h, fdf->map_i.map_w);
	ft_printf("Height :: %d \n", height);
	y_top = map_point_y(0, 0, fdf->map_i.map[0][0], fdf);
	y_bottom = map_point_y(fdf->map_i.map_h - 1, fdf->map_i.map_w - 1, fdf->map_i.map[fdf->map_i.map_h - 1][fdf->map_i.map_w - 1], fdf);
	ft_printf("y_top x y_bottom :: %d x %d :: diff = %d\n", y_top, y_bottom, find_diff(y_top, y_bottom));
	height += find_diff(y_top, y_bottom);
	ft_printf("Height x Width :: %d x %d\n", height, width);
	depth_h = WIN_HEIGHT / height;
	depth_w = WIN_WIDTH / width;
	ft_printf("d-Height x d-Width :: %d x %d\n", depth_h, depth_w);
	if (depth_h > depth_w)
		fdf->map_i.z_depth = depth_w;
	else
		fdf->map_i.z_depth = depth_h;
	width *= fdf->map_i.z_depth;
	height *= fdf->map_i.z_depth;
	fdf->camera.x_offset = WIN_WIDTH - width;
	fdf->camera.y_offset = WIN_HEIGHT - height;
	ft_printf("FIN : Height x Width :: %d x %d\n", height, width);
	ft_printf("fin_depth = %d\n", fdf->map_i.z_depth);
	ft_printf("X-offs = %d, Y-offs = %d\n", fdf->camera.x_offset, fdf->camera.y_offset);
	ft_printf("CAMERA init: All good\n");
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
		// ft_printf("Bpp: %d, win_w = %d, win_h = %d line_len = %d\n", fdf.bits_per_pixel, WIN_WIDTH, WIN_HEIGHT, fdf.line_length);
		mlx_loop(fdf.mlx);
	}
	exit_on_error(ERR_ARGS);
	return (0);
}

/*

*/