/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 14:33:27 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/21 09:16:36 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "ft_printf.h"
# include "mlx.h"

# define WIN_WIDTH		1200
# define WIN_HEIGHT		800

int			g_col_red;
int			g_col_orange;
int			g_col_yellow;
int			g_col_green;
int			g_col_blue;
int			g_col_violet;

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
	int			**map;
	int			**color;
}				t_map;

typedef struct s_point {
	int					x;
	int					y;
	int					z;
	int					color;
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
	t_camera	*camera;
	t_map		map_i;
}				t_fdf;

/* Init program functions */
void	init_map(char *map_file, t_fdf *fdf);
void	register_hooks(t_fdf *fdf);

/* Init map functions */
void	list_to_arr(t_point *flat_map, t_fdf *fdf);
void	map_to_arr(t_point *flat_map, t_fdf *fdf);
void	color_to_arr(t_point *flat_map, t_fdf *fdf);

/* Error management */
void	exit_on_error(char	*msg);

/* Free memory functions */
void	free_fdf(t_fdf *fdf);
void	free_arr(int **arr, int depth);
int		free_points(t_point *list);

void	draw_map(t_fdf *fdf, int **map);

/* t_point functions */

t_point	*ft_point_new(char *z);
t_point	*ft_point_last(t_point *lst);
void	add_line_front(t_point **start, t_point *new);
void	ft_point_add_front(t_point **start, t_point *new);
void	ft_point_add_back(t_point **start, t_point *new);

#endif
