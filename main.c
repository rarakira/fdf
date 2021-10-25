/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/25 14:17:47 by lbaela           ###   ########.fr       */
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
	fdf->map_i.z_depth = 1;
	fdf->map_i.map_h = 0;
	fdf->camera.zoom = 1.0;
	fdf->camera.x_offset = 0;
	fdf->camera.y_offset = 0;
	fdf->camera.xx = 0.0;
	fdf->camera.yy = 0.0;
	fdf->camera.zz = 0.0;
	ft_printf("FDF init: All good\n");
}

static int	here_map_point_x(int x, int y, int z, t_fdf *fdf)
{
	double	x_cart;
	(void)	z;

	x_cart = (x - y) * cos(RAD_ANGLE);
	return ((int)(x_cart * fdf->map_i.z_depth));
}

static int	here_map_point_y(int x, int y, int z, t_fdf *fdf)
{
	double	y_cart;

	y_cart = -z + (x + y) * sin(RAD_ANGLE);
	return ((int)(y_cart * fdf->map_i.z_depth));
}

void	init_camera(t_fdf *fdf)
{
	int	width;
	int	height;
	int	depth_h;
	int	depth_w;

	ft_printf("CAM INIT : Started\n");
	ft_printf("fdf->map_i.map_w - 1 = %d\n", fdf->map_i.map_w - 1);
	ft_printf("left: %d || right: %d\n", here_map_point_x(fdf->map_i.map_w - 1, 0, 0, fdf), here_map_point_x(0, fdf->map_i.map_h - 1, 0, fdf));
	width = here_map_point_x(fdf->map_i.map_w - 1, 0, 0, fdf) - here_map_point_x(0, fdf->map_i.map_h - 1, 0, fdf);
	ft_printf("w = %d\n", width);
	if (fdf->map_i.z_min < 0 && fdf->map_i.z_max < 0)
		height = fdf->map_i.z_min - fdf->map_i.z_max;
	else
		height = fdf->map_i.z_max - fdf->map_i.z_min;
	height += here_map_point_y(fdf->map_i.map_h - 1, fdf->map_i.map_w - 1, 0, fdf);
	ft_printf("h = %d\n", height);
	depth_h = IMG_HEIGHT / height;
	depth_w = IMG_WIDTH / width;
	ft_printf("d_w = %d, d_h = %d\n", depth_w, depth_h);
	if (depth_h > depth_w)
		fdf->map_i.z_depth = depth_w;
	else
		fdf->map_i.z_depth = depth_h;
	width *= fdf->map_i.z_depth;
	height *= fdf->map_i.z_depth;
	fdf->camera.x_offset = WIN_WIDTH / 2;
	fdf->camera.y_offset = 50 + height / 2;
	ft_printf("PROJECTION : Height x Width :: %d x %d\n", height, width);
	ft_printf("z_depth = %d\n", fdf->map_i.z_depth);
	ft_printf("X-offs = %d, Y-offs = %d\n", fdf->camera.x_offset, fdf->camera.y_offset);
	ft_printf("CAMERA init: All good\n");
}

void	print_matrix(t_fdf *fdf)
{
	for (int i = 0; i < fdf->map_i.map_h; i++)
	{
		for (int j = 0; j < fdf->map_i.map_w; j++)
		{
			ft_printf("%d\t", fdf->map_i.map[i][j]);
		}
		ft_printf("\n");
	}
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc == 2)
	{
		init_fdf(&fdf);
		init_map(argv[1], &fdf);
		ft_printf("MAP init: success\n map_w = %d, map_h = %d, z_min = %d, z_max = %d\n", fdf.map_i.map_w, fdf.map_i.map_h, fdf.map_i.z_min, fdf.map_i.z_max);
		//print_matrix(&fdf);
		init_mlx(&fdf);
		init_camera(&fdf);
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
*/
