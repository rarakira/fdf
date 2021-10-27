/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 17:37:27 by lbaela           ###   ########.fr       */
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
	fdf->camera.iso = 1;
	fdf->camera.zoom = 1.0;
	fdf->camera.x_offset = 0;
	fdf->camera.y_offset = 0;
	fdf->camera.xx = 0.0;
	fdf->camera.yy = 0.0;
	fdf->camera.zz = 0.0;
	ft_printf("FDF init: All good\n");
}

void	init_camera(t_fdf *fdf)
{
	int	width;
	int	height;
	int	depth_h;
	int	depth_w;

	width = (fdf->map_i.map_w + fdf->map_i.map_h) * cos(RAD_ANGLE);
	height = (int) find_diff(fdf->map_i.z_max, fdf->map_i.z_min);
	height += (fdf->map_i.map_h + fdf->map_i.map_w) * sin(RAD_ANGLE);
	depth_h = round(WIN_HEIGHT / (float) height);
	depth_w = round(WIN_WIDTH / (float) width);
	if (depth_h > depth_w)
		fdf->map_i.z_depth = depth_w;
	else
		fdf->map_i.z_depth = depth_h;
	width *= fdf->map_i.z_depth;
	height *= fdf->map_i.z_depth;
	fdf->camera.x_offset = WIN_WIDTH / 2;
	fdf->camera.y_offset = 100 + height / 2;
	ft_printf("PROJECTION : Height x Width :: %d x %d\n", height, width);
	ft_printf("CAMERA init: All good\n");
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc == 2)
	{
		init_fdf(&fdf);
		init_map(argv[1], &fdf);
		ft_printf("MAP init: success\n");
		ft_printf("Map_w = %d, map_h = %d, z_min = %d, z_max = %d\n",
			fdf.map_i.map_w, fdf.map_i.map_h, fdf.map_i.z_min, fdf.map_i.z_max);
		init_mlx(&fdf);
		init_camera(&fdf);
		register_hooks(&fdf);
		draw_map(&fdf);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		mlx_loop(fdf.mlx);
	}
	exit_on_error(ERR_ARGS);
	return (0);
}
