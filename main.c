/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 16:00:54 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/19 15:49:38 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "error_messages.h"

int		g_col_red = 0x00D13632;
int		g_col_orange = 0x00E2571E;
int		g_col_yellow = 0x00CDB924;
int		g_col_green = 0x00479E1B;
int		g_col_blue = 0x001D829E;
int		g_col_violet = 0x00503FA9;

void	exit_on_error(char	*msg)
{
	ft_putendl_fd(msg, 1);
	//getchar();
	exit(1);
}

void	init_fdf(t_fdf	*fdf)
{
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "Fdf");
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel,
			&fdf->line_length, &fdf->endian);
}

int	main(int argc, char **argv)
{
	t_fdf		fdf;

	if (argc == 2)
	{
		init_map(argv[1], &fdf);
		//ft_printf("map h = %d, map w = %d\n", fdf.map_info.map_h, fdf.map_info.map_w);
		ft_printf("Exit!\n");
		//getchar();
		init_fdf(&fdf);
		draw_map(&fdf, fdf.map_info.map);
		mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
		//init_camera(fdf.camera);
		//register_hooks(&fdf);
		mlx_loop(fdf.mlx);
		//free_fdf()
	}
	exit_on_error(ERR_ARGS);
	return (0);
}
