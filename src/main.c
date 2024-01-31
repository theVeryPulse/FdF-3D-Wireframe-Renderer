/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:48 by Philip            #+#    #+#             */
/*   Updated: 2024/01/31 21:23:59 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

// Put pixel onto the image.
void	put_pixel_img(t_img_vars *img_vars, int x, int y, int color)
{
	unsigned char	*dst;
	ptrdiff_t		offset;

	offset = y * img_vars->line_size + x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = color;
}

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	draw_diagonal_line(t_img_vars *image, t_coord start, t_coord end, int color)
{
	t_coord	point;
	int		xstep;
	int		ystep;
	
	if (!image || ft_abs(end.x - start.x) != ft_abs(end.y - start.y))
		return ;
	if (start.x > end.x)
	{
		swap(&start.x, &end.x);
		swap(&start.y, &end.y);
	}
	point = start;
	ystep = 1 + (end.y < start.y) * (-2);
	while (point.x <= end.x)
	{
		put_pixel_img(image, point.x, point.y, color);
		point.x++;
		point.y += ystep;
	}
}
void	draw_grid_line(t_img_vars *img_vars, t_coord start, t_coord end, int color)
{
	t_coord	point;

	if (end.x == start.x)
	{
		if (start.y > end.y)
			swap(&start.y, &end.y);
		point = start;
		while (point.y <= end.y)
		{
			put_pixel_img(img_vars, point.x, point.y++, color);
		}
		return ;
	}
	if (end.y == start.y)
	{
		if (start.x > end.x)
			swap(&start.x, &end.x);
		point = start;
		while (point.x <= end.x)
		{
			put_pixel_img(img_vars, point.x++, point.y, color);
		}
		return ;
	}
}

void	draw_line(t_img_vars *img_vars, t_coord start, t_coord end, int color)
{
	bool	slope_greater_than_1;
	bool	slope_is_negative;
	int		delta_y;
	int		delta_x;
	int		diff;
	t_coord	point;

	if (start.x > end.x)
	{
		swap(&start.x, &end.x);
		swap(&start.y, &end.y);
	}

	delta_x = ft_abs(end.x - start.x);
	delta_y = ft_abs(end.y - start.y);
	if (delta_x == delta_y)
	{
		draw_diagonal_line(img_vars, start, end, color);
		return ;
	}
	if (delta_x == 0 || delta_y == 0)
	{
		draw_grid_line(img_vars, start, end, color);
		return ;
	}
	/* Slope > 1 */
	if (delta_y > delta_x)
	{
		swap(&start.x, &start.y);
		swap(&end.x, &end.y);
		delta_x = ft_abs(end.x - start.x);
		delta_y = ft_abs(end.y - start.y);
		slope_greater_than_1 = true;
	}
	else
	{
		slope_greater_than_1 = false;
	}

	/* Slope < 0 */
	if ((end.x - start.x < 0) ^ (end.y - start.y < 0))
	{
		start.y *= -1;
		end.y *= -1;
		slope_is_negative = true;
	}
	else
	{
		slope_is_negative = false;
	}
	diff = 2 * delta_y - delta_x;
	point = start;
	while (point.x <= end.x)
	{
		if (slope_is_negative)
		{
			// printf("(%d,%d)\n", point.x, -point.y);
			put_pixel_img(img_vars, point.x, -point.y, 0xFFFFFF);
		}
		else if (slope_greater_than_1)
		{
			// printf("(%d,%d)\n", point.y, point.x);
			put_pixel_img(img_vars, point.y, point.x, 0xFFFFFF);
		}
		else
		{
			// printf("(%d,%d)\n", point.x, point.y);
			put_pixel_img(img_vars, point.x, point.y, 0xFFFFFF);
		}
		if (diff > 0)
		{
			point.y++;
			diff += 2 * (delta_y - delta_x);
		}
		else
		{
			diff += 2 * delta_y;
		}
		point.x++;
	}
}

void	fill_image_with_color(t_img_vars *img_vars, int color)
{
	t_pixel	x;
	t_pixel	y;

	x = 0;
	y = 0;
	if (!img_vars)
		return ;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			put_pixel_img(img_vars, x, y, color);
			y++;
		}
		x++;
	}
}

void	change_screen_color(t_vars *vars, int color)
{
	if (!vars)
		return ;
	fill_image_with_color(&vars->img_vars, color);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_vars.img_ptr, 0, 0);
}

int	destroy_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	exit (0);
}

int	handle_key(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
	{
		destroy_exit(vars);
	}
	else if (key == XK_r)
	{
		change_screen_color(vars, create_argb(200, 0, 0, 1));
	}
	else if (key == XK_b)
	{
		change_screen_color(vars, create_argb(0, 0, 0, 0));
	}
}

void	mouse_button(int button,int x,int y, void *p)
{
	printf("Mouse in Win, button %d at %dx%d.\n", button, x, y);
}

int	mouse_motion(int x,int y, void *p)
{
  printf("Mouse moving in Win, at %dx%d.\n",x,y);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	char	*content;
	t_map	map;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]);
	printf("Content as one string:\n%s", content);
	map_check(content);
	printf("Map checked\n");
	map = build_map(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");

	// Put a string in window
	// mlx_string_put(mlx_ptr, win_ptr, WIDTH / 2, HEIGHT / 2, color, "Hello World!");

	// Draw a line in window
	/* for (int i = 0; i < WIDTH; i++)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, i, HEIGHT / 2, 0x00ff00);
	} */

	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT); // creates a new image in memory. It returns a void * identifier needed to manipulate this image later
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	

	/* Draw a rectangle */
	t_coord	left_top = {100, 100};
	t_coord	right_bottom = {WIDTH - 100, HEIGHT - 100};

	/* Slope > 1 */
	draw_line(&vars.img_vars, (t_coord){0, 0}, (t_coord){10, 1000}, 0xFFFFFF);
	/* Slope < 0 */
	draw_line(&vars.img_vars, (t_coord){0, 1000}, (t_coord){1000, 500}, 0xFFFFFF);
	// draw_line(&img, (t_coord){960, 540}, (t_coord){1900, 1000}, 0xFFFFFF);
	// draw_line(&img, (t_coord){960, 540}, (t_coord){900, 0}, 0xFFFFFF);

	// draw_line(&img, (t_coord){0, 0}, (t_coord){500, 500}, 0xFFFFFF);

	/* t_coord center = (t_coord){1920 / 2, 1080 / 2};
	draw_line(&img, (t_coord){center.x - 200, center.y}, (t_coord){center.x, center.y + 200}, 0xFFFFFF);
	draw_line(&img, (t_coord){center.x - 200, center.y}, (t_coord){center.x, center.y - 200}, 0xFFFFFF);
	draw_line(&img, (t_coord){center.x, center.y + 200}, (t_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_coord){center.x, center.y - 200}, (t_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_coord){center.x - 200, center.y}, (t_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_coord){center.x, center.y - 200}, (t_coord){center.x, center.y + 200}, 0xFFFFFF); */

	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

	mlx_key_hook(vars.win_ptr, handle_key, &vars);
	mlx_hook(vars.win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_button, &vars);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);

	mlx_loop(vars.mlx_ptr);
}
