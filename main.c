/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/18 07:53:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

void exit_on_error(char	*msg)
{}

int main(int argc, char **argv)
{
	t_fdf		fdf;
	t_map		*map;

	if (argc == 2)
	{
		fdf.mlx = mlx_init();
		fdf.win = mlx_new_window(fdf.mlx, 1200, 800, "Fdf");
		fdf.img = mlx_new_image(fdf.mlx, 1200, 800);
		fdf.addr = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, &fdf.line_length,	 &fdf.endian);
		//map = create_map();
		init_map(map);
		init_fdf(fdf);
		init_camera(fdf.camera);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		//mlx_string_put(fdf.mlx, fdf.win, 20, 20, g_col_orange, "Hello FdF!");
		register_hooks(&fdf);
		mlx_loop(fdf.mlx);
		//free_fdf()
	}
	exit_on_error(ERR_ARGS);
	return 0;
}
