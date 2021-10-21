/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 10:01:50 by lbaela           ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc == 2)
	{
		init_map(argv[1], &fdf);
		init_mlx(&fdf);
		register_hooks(&fdf);
		draw_map(&fdf, fdf.map_i.map);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		ft_printf("Bpp: %d, win_w = %d, win_h = %d line_len = %d\n", fdf.bits_per_pixel, WIN_WIDTH, WIN_HEIGHT, fdf.line_length);
		//init_camera(fdf.camera);
		mlx_loop(fdf.mlx);
	}
	exit_on_error(ERR_ARGS);
	return (0);
}
