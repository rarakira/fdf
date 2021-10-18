#include "includes/fdf.h"
#include "includes/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	int row;
	int col;
	int i = 0;

	col = 0;
	row = 1;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 800, "Fdf");
	img.img = mlx_new_image(mlx, 1200, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	/* Darwing diagonal rainbow */
	while (i++ < 800)
	{
		print_wide(&img, row, col, g_col_red, 10);
		row += 10;
		print_wide(&img, row, col, g_col_orange, 10);
		row += 10;
		print_wide(&img, row, col, g_col_yellow, 10);
		row += 10;
		print_wide(&img, row, col, g_col_green, 10);
		row += 10;
		print_wide(&img, row, col, g_col_blue, 10);
		row += 10;
		print_wide(&img, row, col, g_col_violet, 10);
		col++;
		row -= 49;
	}
	/* Drawing circle */
	draw_circle(&img, 200, 200, 50, 0x00FFFFFF);
	draw_shaded_circle(&img, 750, 400, 120, 0x00FFFFFF);
	draw_shaded_circle(&img, 800, 350, 150, g_col_red);
	draw_shaded_circle(&img, 800, 350, 140, g_col_orange);
	draw_shaded_circle(&img, 800, 350, 130, g_col_yellow);
	draw_shaded_circle(&img, 800, 350, 120, g_col_green);
	draw_shaded_circle(&img, 800, 350, 110, g_col_blue);
	draw_shaded_circle(&img, 800, 350, 100, g_col_violet);
	draw_shaded_circle(&img, 800, 350, 90, 0x0);
	draw_circle(&img, 750, 400, 300, 0x00FFFFFF);
	draw_circle(&img, 750, 400, 299, 0x00FFFFFF);
	int n = 0;
	while (n++ < 20)
	{
		draw_shaded_circle(&img, 250 + (n * 5), 450 + (n * 5), 30, get_grad_color(g_col_yellow, g_col_violet, (0.0 + 0.05 * n)));
	}
	n = 0;
	while (n < 50)
	{
		//printf("1 [[ %d ]], n %% 10 = %d\n", n, n % 10);
		if (n < 10)
			draw_shaded_circle(&img, 150 + (n * 5), 650, 30, get_grad_color(g_col_red, g_col_orange, find_percent(0, 9, n % 10)));
		else if (n < 20)
			draw_shaded_circle(&img, 150 + (n * 5), 650, 30, get_grad_color(g_col_orange, g_col_yellow, find_percent(0, 9, n % 10)));
		else if (n < 30)
			draw_shaded_circle(&img, 150 + (n * 5), 650, 30, get_grad_color(g_col_yellow, g_col_green, find_percent(0, 9, n % 10)));
		else if (n < 40)
			draw_shaded_circle(&img, 150 + (n * 5), 650, 30, get_grad_color(g_col_green, g_col_blue, find_percent(0, 9, n % 10)));
		else
			draw_shaded_circle(&img, 150 + (n * 5), 650, 30, get_grad_color(g_col_blue, g_col_violet, find_percent(0, 9, n % 10)));
		//printf("3 percent = %f\n", find_percent(0, 9, n % 10));
		//printf("3 gradient_color = %x\n", get_grad_color(g_col_blue, g_col_violet, find_percent(0, 9, n % 10)));
		n++;
	}
	/* Bresenham's circle */
	circle_bresenhams(&img, 500, 100, 40, g_col_violet);
	/* Bresenham's lines try */
	bresenham_line(&img, 470, 100, 800, 150, g_col_orange);
	bresenham_line(&img, 475, 100, 800, 50, g_col_orange);
	/* Drawing triangle */
	my_draw_line(&img, 470 + 200, 100, 800 + 200, 150, g_col_yellow);
	my_draw_line(&img, 470 + 200, 100, 800 + 200, 50, g_col_yellow);
	my_draw_line(&img, 800 + 200, 50, 800 + 200, 150, g_col_yellow);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

	return 0;
}

/*
int main(void)
{
	void	*mlx;
	void	*mlx_win;

	//Establish a connection to the correct graphical system and will return a ///(void *) which holds the location of our current MLX instance.
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 860, "Hello World!"); //initializing window
	mlx_loop(mlx); // initiate the window rendering
	return 0;
}
*/
