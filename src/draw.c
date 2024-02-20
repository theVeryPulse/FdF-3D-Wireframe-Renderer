/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:30:56 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 22:26:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// Put pixel onto the image.
void	put_pixel_img(t_img_vars *img_vars, t_px_coord coord, t_argb color)
{
	unsigned char	*dst;
	ptrdiff_t		offset;

	if (coord.x >= WIDTH || coord.x < 0 || coord.y >= HEIGHT || coord.y < 0)
		return ;
	offset = coord.y * img_vars->line_size + coord.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = color;
}

void	fill_image_with_color(t_img_vars *img_vars, int color)
{
	t_px_coord	point;

	if (!img_vars)
		return ;
	point = (t_px_coord){0};
	while (point.x < WIDTH)
	{
		point.y = 0;
		while (point.y < HEIGHT)
		{
			put_pixel_img(img_vars, point, color);
			point.y++;
		}
		point.x++;
	}
}

void	draw_diagonal_line(t_img_vars *image, t_px_coord a, t_px_coord b, int color)
{
	t_px_coord	point;
	int		xstep;
	int		ystep;
	
	if (!image || ft_abs(b.x - a.x) != ft_abs(b.y - a.y))
		return ;
	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	point = a;
	ystep = 1 + (b.y < a.y) * (-2);
	while (point.x <= b.x)
	{
		put_pixel_img(image, point, color);
		point.x++;
		point.y += ystep;
	}
}

void	draw_grid_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b, int color)
{
	t_px_coord	point;

	if (b.x == a.x)
	{
		if (a.y > b.y)
			int_swap(&a.y, &b.y);
		point = a;
		while (point.y++ <= b.y)
		{
			put_pixel_img(img_vars, point, color);
		}
		return ;
	}
	if (b.y == a.y)
	{
		if (a.x > b.x)
			int_swap(&a.x, &b.x);
		point = a;
		while (point.x++ <= b.x)
		{
			put_pixel_img(img_vars, point, color);
		}
		return ;
	}
}

void	draw_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b, int color)
{
	bool		slope_greater_than_1;
	bool		slope_is_negative;
	int			delta_y;
	int			delta_x;
	int			error;
	t_px_coord	point;

	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	delta_x = ft_abs(b.x - a.x);
	delta_y = ft_abs(b.y - a.y);
	if (delta_x == delta_y)
	{
		draw_diagonal_line(img_vars, a, b, color);
		return ;
	}
	if (delta_x == 0 || delta_y == 0)
	{
		draw_grid_line(img_vars, a, b, color);
		return ;
	}
	/* Slope < 0 */
	if ((a.x < b.x) && (a.y > b.y))
	{
		a.y = -a.y;
		b.y = -b.y;
		slope_is_negative = true;
	}
	else
	{
		slope_is_negative = false;
	}

	/* Slope > 1 */
	if (delta_y > delta_x)
	{
		int_swap(&a.x, &a.y);
		int_swap(&b.x, &b.y);
		slope_greater_than_1 = true;
	}
	else
	{
		slope_greater_than_1 = false;
	}
	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	delta_x = ft_abs(b.x - a.x);
	delta_y = ft_abs(b.y - a.y);
	error = 2 * delta_y - delta_x;
	point = a;
	while (point.x <= b.x)
	{
		if (slope_greater_than_1 && slope_is_negative)
		{
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x}, WHITE);
			// printf("(%d,%d)\n", point.y, -point.x);
		}
		else if (slope_is_negative)
		{
			// printf("(%d,%d)\n", point.x, -point.y);
			put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y}, WHITE);
		}
		else if (slope_greater_than_1)
		{
			// printf("(%d,%d)\n", point.y, point.x);
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x}, WHITE);
		}
		else
		{
			// printf("(%d,%d)\n", point.x, point.y);
			put_pixel_img(img_vars, point, WHITE);
		}
		if (error > 0)
		{
			point.y++;
			error += 2 * (delta_y - delta_x);
		}
		else
		{
			error += 2 * delta_y;
		}
		point.x++;
	}
}

void	draw_colored_diagonal_line(t_img_vars *image, t_px_coord a, t_px_coord b)
{
	t_px_coord	point;
	int		xstep;
	int		ystep;
	double	t;
	double	dt;
	t_argb	color;

	if (!image || ft_abs(b.x - a.x) != ft_abs(b.y - a.y))
		return ;
	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	t = 0.0;
	dt = 1.0 / ft_abs(b.x - a.x);
	point = a;
	ystep = 1 + (b.y < a.y) * (-2);
	while (point.x <= b.x)
	{
		color = create_argb((0xff),
							((1 - t) * get_r(a.color) + t * get_r(b.color)),
							((1 - t) * get_g(a.color) + t * get_g(b.color)),
							((1 - t) * get_b(a.color) + t * get_b(b.color)));
		/* color.r = (1 - t) * color0.r + t * color1.r;
		color.g = (1 - t) * color0.g + t * color1.g;
		color.b = (1 - t) * color0.b + t * color1.b; */
		put_pixel_img(image, point, color);
		point.x++;
		point.y += ystep;
		t += dt;
	}
}

void	draw_colored_grid_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_px_coord	point;
	double		t;
	double		dt;
	t_argb		color;

	t = 0.0;
	if (b.x == a.x)
	{
		if (a.y > b.y)
			int_swap(&a.y, &b.y);
		dt = 1.0 / ft_abs(b.y - a.y);
		point = a;
		while (point.y++ <= b.y)
		{
			color = create_argb((0xff),
							((1 - t) * get_r(a.color) + t * get_r(b.color)),
							((1 - t) * get_g(a.color) + t * get_g(b.color)),
							((1 - t) * get_b(a.color) + t * get_b(b.color)));
			put_pixel_img(img_vars, point, color);
			t += dt;
		}
		return ;
	}
	if (b.y == a.y)
	{
		if (a.x > b.x)
			int_swap(&a.x, &b.x);
		dt = 1.0 / ft_abs(b.x - a.x);
		point = a;
		while (point.x++ <= b.x)
		{
			color = create_argb((0xff),
							((1 - t) * get_r(a.color) + t * get_r(b.color)),
							((1 - t) * get_g(a.color) + t * get_g(b.color)),
							((1 - t) * get_b(a.color) + t * get_b(b.color)));
			put_pixel_img(img_vars, point, color);
			t += dt;
		}
		return ;
	}
}

void	draw_colored_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	bool		slope_greater_than_1;
	bool		slope_is_negative;
	int			delta_y;
	int			delta_x;
	int			error;
	t_px_coord	point;
	double		t;
	double		dt;
	t_argb		color;

	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	delta_x = ft_abs(b.x - a.x);
	delta_y = ft_abs(b.y - a.y);
	if (delta_x == delta_y)
	{
		draw_colored_diagonal_line(img_vars, a, b);
		return ;
	}
	if (delta_x == 0 || delta_y == 0)
	{
		draw_colored_grid_line(img_vars, a, b);
		return ;
	}
	/* Slope < 0 */
	if ((a.x < b.x) && (a.y > b.y))
	{
		a.y = -a.y;
		b.y = -b.y;
		slope_is_negative = true;
	}
	else
	{
		slope_is_negative = false;
	}

	/* Slope > 1 */
	if (delta_y > delta_x)
	{
		int_swap(&a.x, &a.y);
		int_swap(&b.x, &b.y);
		slope_greater_than_1 = true;
	}
	else
	{
		slope_greater_than_1 = false;
	}
	if (a.x > b.x)
	{
		int_swap(&a.x, &b.x);
		int_swap(&a.y, &b.y);
	}
	delta_x = ft_abs(b.x - a.x);
	delta_y = ft_abs(b.y - a.y);
	error = 2 * delta_y - delta_x;
	point = a;
	t = 0.0;
	dt = 1.0 / ft_abs(b.x - a.x);
	while (point.x <= b.x)
	{
		color = create_argb((0xff),
							((1 - t) * get_r(a.color) + t * get_r(b.color)),
							((1 - t) * get_g(a.color) + t * get_g(b.color)),
							((1 - t) * get_b(a.color) + t * get_b(b.color)));
		if (slope_greater_than_1 && slope_is_negative)
		{
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x}, color);
			// printf("(%d,%d)\n", point.y, -point.x);
		}
		else if (slope_is_negative)
		{
			// printf("(%d,%d)\n", point.x, -point.y);
			
			put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y}, color);
		}
		else if (slope_greater_than_1)
		{
			// printf("(%d,%d)\n", point.y, point.x);
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x}, color);
		}
		else
		{
			// printf("(%d,%d)\n", point.x, point.y);
			put_pixel_img(img_vars, point, color);
		}
		if (error > 0)
		{
			point.y++;
			error += 2 * (delta_y - delta_x);
		}
		else
		{
			error += 2 * delta_y;
		}
		point.x++;
		t += dt;
	}
}
