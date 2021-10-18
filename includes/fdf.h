/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:33:27 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/18 16:04:37 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# define WIN_WIDTH		1200
# define WIN_HEIGHT		800

typedef struct s_camera {
	int		iso;
	int		x_offset;
	int		y_offset;
	int		zoom;
}				t_camera;

typedef struct s_map {
	int			map_h;
	int			map_w;
	int			z_depth;
	int			z_min;
	int			z_max;
}				t_map;

typedef struct s_point {
	int					x;
	int					y;
	int					z;
	struct s_point		*next;
}						t_point;

typedef struct s_fdf {
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_point		**map;
	t_camera	*camera;
	t_map		*map_info;
}				t_fdf;

t_point	**init_map(char	*map_file);
void	exit_on_error(char	*msg);

#endif
