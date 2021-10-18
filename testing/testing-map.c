#include "includes/fdf.h"
#include "includes/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int g_col_red = 0x00D13632;
int g_col_orange = 0x00E2571E;
int g_col_yellow = 0x00CDB924;
int g_col_green = 0x00479E1B;
int g_col_blue = 0x001D829E;
int g_col_violet = 0x00503FA9;

int create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int get_b(int trgb)
{
	return (trgb & 0xFF);
}

/* 
0 will add no shading to the color, whilst 1 will make the color completely dark. 0.5 will dim it halfway, and .25 a quarter way.
*/
//should check later
int add_shade(double distance, int color)
{
	int r;
	int g;
	int b;
	double ratio;

	ratio = 1.0 - distance;
	r = (int)(get_r(color) * ratio);
	g = (int)(get_g(color) * ratio);
	b = (int)(get_b(color) * ratio);
	return (get_t(color) | (r << 16) | (g << 8) | b);
}

int make_darker(double darken, int color)
{
	int r;
	int g;
	int b;

	r = (int)(get_r(color) * darken);
	g = (int)(get_g(color) * darken);
	b = (int)(get_b(color) * darken);
	return (get_t(color) | (r << 16) | (g << 8) | b);
}

/*
accepts a int (color) as argument and that will invert the color accordingly
*/
int get_opposite(int trgb)
{
	return (trgb ^ 0x00FFFFFF);
}

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void print_wide(t_data *img, int x, int y, int color, int width)
{
	int i = 0;

	while (i < width)
		my_mlx_pixel_put(img, (i++ + x), y, color);
}

int color_randomiser(void)
{
	return (rand() % 0x00FFFFFF);
}

void draw_circle(t_data *img, int x_center, int y_center, int radius, int color)
{
	int x;
	int y;
	int P;

	x = radius;
	y = 0;
	my_mlx_pixel_put(img, x + x_center, y + y_center, color);
	if (radius > 0)
	{
		my_mlx_pixel_put(img, -x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, y + x_center, x + y_center, color);
		my_mlx_pixel_put(img, y + x_center, -x + y_center, color);
	}
	P = 1 - radius;
	while (x > y)
	{
		y++;
		//color = color_randomiser();
		if (P <= 0)
			P = P + 2 * y + 1;
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}
		if (x < y)
			break;
		my_mlx_pixel_put(img, x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, -x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, x + x_center, -y + y_center, color);
		my_mlx_pixel_put(img, -x + x_center, -y + y_center, color);
		if (x != y)
		{
			my_mlx_pixel_put(img, y + x_center, x + y_center, color);
			my_mlx_pixel_put(img, -y + x_center, x + y_center, color);
			my_mlx_pixel_put(img, y + x_center, -x + y_center, color);
			my_mlx_pixel_put(img, -y + x_center, -x + y_center, color);
		}
	}
}

void draw_shaded_circle(t_data *img, int x_center, int y_center, int radius, int color)
{
	int x;
	int y;
	int P;

	x = radius;
	y = 0;
	my_mlx_pixel_put(img, x + x_center, y + y_center, color);
	if (radius > 0)
	{
		print_wide(img, -x + x_center, y + y_center, color, x * 2);
		my_mlx_pixel_put(img, -x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, y + x_center, x + y_center, color);
		my_mlx_pixel_put(img, y + x_center, -x + y_center, color);
	}
	P = 1 - radius;
	while (x > y)
	{
		y++;
		//color = color_randomiser();
		if (P <= 0)
			P = P + 2 * y + 1;
		else
		{
			x--;
			P = P + 2 * y - 2 * x + 1;
		}
		if (x < y)
			break;
		print_wide(img, -x + x_center, y + y_center, color, x * 2);
		print_wide(img, -x + x_center, -y + y_center, color, x * 2);
		my_mlx_pixel_put(img, x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, -x + x_center, y + y_center, color);
		my_mlx_pixel_put(img, x + x_center, -y + y_center, color);
		my_mlx_pixel_put(img, -x + x_center, -y + y_center, color);
		if (x != y)
		{
			print_wide(img, -y + x_center, x + y_center, color, y * 2);
			print_wide(img, -y + x_center, -x + y_center, color, y * 2);
			my_mlx_pixel_put(img, y + x_center, x + y_center, color);
			my_mlx_pixel_put(img, -y + x_center, x + y_center, color);
			my_mlx_pixel_put(img, y + x_center, -x + y_center, color);
			my_mlx_pixel_put(img, -y + x_center, -x + y_center, color);
		}
	}
}

void draw_8points(t_data *img, int xc, int yc, int x, int y, int color)
{
	my_mlx_pixel_put(img, xc + x, yc + y, color);
	my_mlx_pixel_put(img, xc - x, yc + y, color);
	my_mlx_pixel_put(img, xc + x, yc - y, color);
	my_mlx_pixel_put(img, xc - x, yc - y, color);
	my_mlx_pixel_put(img, xc + y, yc + x, color);
	my_mlx_pixel_put(img, xc - y, yc + x, color);
	my_mlx_pixel_put(img, xc + y, yc - x, color);
	my_mlx_pixel_put(img, xc - y, yc - x, color);
}

void circle_bresenhams(t_data *img, int xc, int yc, int r, int color)
{
	int x = 0, y = r;
	int d = 3 - 2 * r;
	//printf("x = %d, y = %d, d = %d\n", x, y, d);
	draw_8points(img, xc, yc, x, y, color);
	while (y >= x)
	{
		x++;
		if (d > 0) //(x+1, y-1)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else //(x+1, y)
			d = d + 4 * x + 6;
		//printf("x = %d, y = %d, d = %d\n", x, y, d);
		//if (x == 1)
		//	draw_8points(img, xc, yc, x, y, g_col_yellow);
		//else if (x == 8)
		//	draw_8points(img, xc, yc, x, y, g_col_orange);
		//else if (x == 16)
		//	draw_8points(img, xc, yc, x, y, g_col_red);
		//else
		draw_8points(img, xc, yc, x, y, color);
	}
}

int find_diff(int a, int b)
{
	int diff;

	diff = a - b;
	if (diff < 0)
		return (diff * -1);
	return (diff);
}

void bresenham_line(t_data *img, int x_start, int y_start, int x_end, int y_end, int color)
{
	int m_new = 2 * (y_end - y_start);
	int slope_error_new = m_new - (x_end - x_start);
	my_mlx_pixel_put(img, x_start, y_start, color);
	for (int x = x_start, y = y_start; x <= x_end; x++)
	{
		// Add slope to increment angle formed
		slope_error_new += m_new;

		// Slope error reached limit, time to
		// increment y and update slope error.
		if (slope_error_new >= 0)
		{
			y++;
			slope_error_new -= 2 * (x_end - x_start);
		}
		my_mlx_pixel_put(img, x, y, color);
	}
}

void my_draw_line(t_data *img, int x_start, int y_start, int x_end, int y_end, int color)
{
	double x;
	double y;
	double increment_x;
	double increment_y;

	x = x_start;
	y = y_start;
	increment_y = 1.0;
	if (y_start > y_end)
		increment_y = -1.0;
	increment_x = 1.0;
	if (x_start > x_end)
		increment_x = -1.0;
	int diff_x = find_diff(x_start, x_end);
	int diff_y = find_diff(y_start, y_end);
	my_mlx_pixel_put(img, x, y, color);
	if (diff_x < diff_y)
	{
		increment_x *= diff_x / (float) diff_y;
		while (y != y_end)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(img, round(x), round(y), color);
		}
	}
	else
	{
		increment_y *= diff_y / (float) diff_x;
		while (x != x_end)
		{
			y += increment_y;
			x += increment_x;
			my_mlx_pixel_put(img, round(x), round(y), color);
		}
	}
	my_mlx_pixel_put(img, x_end, y_end, color);
}

double find_percent(int start, int end, int current)
{
	double placement;
	double distance;

	//printf("2 start = %d, end = %d, current = %d\n", start, end, current);
	if (current == start)
		return (0.0);
	placement = current - start;
	distance = end - start;
	//printf("2 placement = %f, distance = %f\n", placement, distance);
	if (distance == 0)
		return (1.0);
	//printf("2 [placement / distance]\t = %f\n", placement / distance);
	return (placement / distance);
}

int get_tint(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int get_grad_color(int start, int end, double percentage)
{
	int red;
	int green;
	int blue;

	red = get_tint((start >> 16) & 0xFF, (end >> 16) & 0xFF, percentage);
	green = get_tint((start >> 8) & 0xFF, (end >> 8) & 0xFF, percentage);
	blue = get_tint(start & 0xFF, end & 0xFF, percentage);
	return ((red << 16) | (green << 8) | blue);
}

int	key_hook(int keycode, t_vars *vars)
{
	(void) vars;
	printf("Hello from key_hook - [%d]!\n", keycode);
	return (1);
}

int	fdf_close(int keycode, t_vars *vars)
{
	(void) vars;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit (1);
	}
	return (0);
}

int	fdf_close_x(t_vars *vars)
{
	(void) vars;
	mlx_destroy_window(vars->mlx, vars->win);
	printf("Exiting program, bye!\n");
	sleep(30);
	exit (1);
	return (0);
}

int	enter_mouse(int button, int x, int y, t_vars *vars) //not working
{
	(void) vars;
	(void) button;
	printf("Mouse ENTERED window at (%d, %d) !\n", x, y);
	return (1);
}

int	enter_mouse2(t_vars *vars)
{
	(void)vars;
	printf("PTR ENTER WINDOW\n");
	return (0);
}

int	leave_mouse(t_vars *vars) //not working
{
	(void) vars;
	printf("Mouse LEFT window at !\n");
	return (1);
}

int	mouse_hook(int button, int x, int y, t_vars *vars)
{
	(void) vars;
	printf("Mouse (button = %d) pressed - (%d, %d) !\n", button, x, y);
	return (1);
}

int	resize_request(t_vars *vars)
{
	(void) vars;
	printf("Resizing window!\n");
	return (0);
}

typedef struct	s_point {
	int	x;
	int	y;
	int z;
}				t_point;

t_point	*create_map(void)
{
	t_point	*ptr;
	int	i = 0;
	int	j;

	ptr = malloc(sizeof(t_point) * 11 * 5);
	if (!ptr)
		return (NULL);
	while (i < 11)
	{
		j = 0;
		while (j < 5)
		{
			//printf("i = %d, j = %d, *(ptr + i) = %p, %zu\n", i, j, (ptr + (i * 5) + j), sizeof((ptr + (i * 5) + j)));
			(ptr + (i * 5) + j)->x = i;
			(ptr + (i * 5) + j)->y = j;
			(ptr + (i * 5) + j)->z = 0;
			//if (j == 2)
			//	(ptr + (i * 5) + j)->z = 2;
			j++;
		}
		i++;
	}
	return (ptr);
}

int	map_point_x(t_point *point)
{
	//printf("MAP X:\npoint->x = %d, point->y = %d, point->z = %d\n", point->x, point->y, point->z);
	//printf("sum = %d\n", point->x * 1 + point->y * 1 + point->z * 0);
	return ((int)((point->x * 1 + point->y * 1 + point->z * 0) * 20));
}

int	map_point_y(t_point *point)
{
	//printf("MAP Y:\npoint->x = %d, point->y = %d, point->z = %d\n", point->x, point->y, point->z);
	//printf("sum = %f\n", (point->x * (-0.5) + point->y * 0.5 + point->z * 1));
	return ((int)((point->x * (-0.5) + point->y * 0.5 + point->z * 1) * 20));
}

int main(void)
{
	t_vars		vars;
	t_data		img;
	t_point		*ptr;


	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1200, 800, "Fdf");
	img.img = mlx_new_image(vars.mlx, 1200, 800);
	//printf("Before: Bits_p_p = %d; line_len = %d, endian = %d\n", img.bits_per_pixel, img.line_length, img.endian);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian); // returns char * – the beginning of the image memory chunk
	//printf("After: Bits_p_p = %d; line_len = %d, endian = %d\n", img.bits_per_pixel, img.line_length, img.endian);
	ptr = create_map();

	/* Drawing map */
	int		x_start, y_start;
	int		x_fin, y_fin;
	int		n = 5;

	for (int k = 0; k < 10; k++)
	{
		for (int m = 0; m < n; m++)
		{
			//printf("k = %d, m = %d\n", k, m);
			if (m < 4) // draw horizontal
			{
				//printf("HOR: point1 %p, point2 %p\n", (ptr + k * n + m), (ptr + k * n + m + 1));
				x_start = map_point_x(ptr + k * n + m);
				y_start = map_point_y(ptr + k * n + m);
				x_fin = map_point_x(ptr + k * n + m + 1);
				y_fin = map_point_y(ptr + k * n + m + 1);
				//printf("%d | %d HOR: start[%d, %d], fin[%d, %d]\n", k, m, x_start, y_start, x_fin, y_fin);
				my_draw_line(&img, 450 + x_start, 400 + y_start, 450 + x_fin, 400 + y_fin, g_col_yellow);
			}
			if (k < 9) // draw vertical
			{
				//printf("VER: point1 %p, point2 %p\n", (ptr + k * n + m), (ptr + (k + 1) * n + m));
				x_start = map_point_x(ptr + k * n + m);
				y_start = map_point_y(ptr + k * n + m);
				x_fin = map_point_x(ptr + (k + 1) * n + m);
				y_fin = map_point_y(ptr + (k + 1) * n + m);
				//printf("%d | %d VER: start[%d, %d], fin[%d, %d]\n", k, m, x_start, y_start, x_fin, y_fin);
				if (k % 2)
					my_draw_line(&img, 450 + x_start, 400 + y_start, 450 + x_fin, 400 + y_fin, g_col_violet);
				else if (k % 3)
					my_draw_line(&img, 450 + x_start, 400 + y_start, 450 + x_fin, 400 + y_fin, g_col_green);
				else
					my_draw_line(&img, 450 + x_start, 400 + y_start, 450 + x_fin, 400 + y_fin, g_col_red);
			}
		}
	}
	/*
	for (int k = 0; k < 11; k++)
	{
		for (int m = 0; m < 5; m++)
		{
			printf("point %p: x = %d, y = %d, z = %d\n", (ptr + k * 5 + m), (ptr + k * 5 + m)->x, (ptr + k * 5 + m)->y, (ptr + k * 5 + m)->z);
		}
	}
	*/
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_string_put(vars.mlx, vars.win, 20, 20, g_col_orange, "Hello FdF!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, (1L<<0), fdf_close, &vars);
	mlx_hook(vars.win, 17, (1L<<17), fdf_close_x, &vars);
	mlx_hook(vars.win, 7, (1L<<4), enter_mouse2, &vars);
	mlx_hook(vars.win, 8, 0L, leave_mouse, &vars);
	mlx_hook(vars.win, 25, 1L<<18, resize_request, &vars);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);

	return 0;
}
