/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:33:27 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/18 07:49:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

typedef struct	s_camera {
	int		iso;
	int		x_offset;
	int		y_offset;
	int		zoom;
}				t_camera;

typedef struct	s_fdf {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_camera	camera;
}				t_fdf;

typedef struct	s_point {
	int		x;
	int		y;
	int		z;
}				t_point;

typedef struct	s_map {
	int		map_h;
	int		map_w;
	int		z_depth;
	int		z_min;
	int		z_max;
}				t_map;


#endif
