/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:30:56 by Philip            #+#    #+#             */
/*   Updated: 2024/02/23 18:20:57 by Philip           ###   ########.fr       */
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

void	px_coord_swap(t_px_coord *a, t_px_coord *b)
{
	t_px_coord	tmp;

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
	offset = coord.y * img_vars->line_size
			+ coord.x * (img_vars->bits_per_pixel / 8);
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

t_argb	gradient_color(double transition, t_argb start, t_argb end)
{
	t_argb	color;

	if (transition < 0 || transition > 1)
		return (start);
	color = argb((0xff),
				((1 - transition) * get_r(start) + transition * get_r(end)),
				((1 - transition) * get_g(start) + transition * get_g(end)),
				((1 - transition) * get_b(start) + transition * get_b(end)));
	return (color);
}

void	draw_colored_diagonal_line(t_img_vars *image, t_px_coord a, t_px_coord b)
{
	t_px_coord	point;
	int		xstep;
	int		ystep;
	double	t;
	double	dt;

	if (!image || ft_abs(b.x - a.x) != ft_abs(b.y - a.y))
		return ;
	if (a.x > b.x)
		px_coord_swap(&a, &b);
	t = 0.0;
	dt = 1.0 / ft_abs(b.x - a.x);
	point = a;
	ystep = 1 + (b.y < a.y) * (-2);
	while (point.x <= b.x)
	{
		put_pixel_img(image, point, gradient_color(t, a.color, b.color));
		point.x++;
		point.y += ystep;
		t += dt;
	}
}

void	draw_colored_hori_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_px_coord	point;
	double		t;
	double		dt;
	t_argb		color;

	if (a.x != b.x)
		return ;
	if (a.x > b.x)
			int_swap(&a.x, &b.x);
	dt = 1.0 / ft_abs(b.x - a.x);
	point = a;
	while (point.x++ <= b.x)
	{
		color = gradient_color(t, a.color, b.color);
		put_pixel_img(img_vars, point, color);
		t += dt;
	}
}

void	draw_colored_verti_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_px_coord	point;
	double		t;
	double		dt;
	t_argb		color;

	if (b.y != a.y)
		return ;
	if (a.y > b.y)
		int_swap(&a.y, &b.y);
	dt = 1.0 / ft_abs(b.y - a.y);
	point = a;
	while (point.y++ <= b.y)
	{
		color = gradient_color(t, a.color, b.color);
		put_pixel_img(img_vars, point, color);
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
		draw_colored_verti_line(img_vars, a, b);
	else if (b.y == a.y)
		draw_colored_hori_line(img_vars, a, b);
}

void	draw_pixel_bresenham(t_img_vars *img_vars, t_slope_property slope, t_px_coord point)
{
	if (!img_vars)
		return ;
	if (slope.is_greater_than_1 && slope.is_negative)
		put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x}, point.color);
	else if (slope.is_negative)
		put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y}, point.color);
	else if (slope.is_greater_than_1)
		put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x}, point.color);
	else
		put_pixel_img(img_vars, point, point.color);
}

void	calc_error_and_delta(int *error, t_delta *delta, t_px_coord *a, t_px_coord *b)
{
	delta->x = ft_abs(b->x - a->x);
	delta->y = ft_abs(b->y - a->y);
	*error = 2 * delta->y - delta->x;
}

void	init_transition(t_transition *t, t_px_coord *a, t_px_coord *b)
{
	t->curr = 0.0;
	t->step = 1.0 / ft_abs(b->x - a->x);
}

void	draw_colored_pixels_bresenham(t_img_vars *img_vars,
					t_px_coord a,
					t_px_coord b,
					t_slope_property slope)
{
	t_px_coord		point;
	t_transition	t;
	int				error;
	t_delta			delta;

	calc_error_and_delta(&error, &delta, &a, &b);
	init_transition(&t, &a, &b);
	point = a;
	while (point.x <= b.x)
	{
		point.color = gradient_color(t.curr, a.color, b.color);
		draw_pixel_bresenham(img_vars, slope, point);
		if (error > 0)
		{
			point.y++;
			error += 2 * (delta.y - delta.x);
		}
		else
			error += 2 * delta.y;
		point.x++;
		t.curr += t.step;
	}
}

void	normalize_coords_bresenham(t_px_coord *a, t_px_coord *b, t_slope_property *slope)
{
	t_delta	delta;

	if (!a || !b || !slope)
		return ;
	if (a->x > b->x)
		px_coord_swap(a, b);
	delta.x = ft_abs(b->x - a->x);
	delta.y = ft_abs(b->y - a->y);
	slope->is_negative = false;
	if ((a->x < b->x) && (a->y > b->y))
	{
		a->y *= -1;
		b->y *= -1;
		slope->is_negative = true;
	}
	slope->is_greater_than_1 = false;
	if (delta.y > delta.x)
	{
		int_swap(&(a->x), &(a->y));
		int_swap(&(b->x), &(b->y));
		slope->is_greater_than_1 = true;
	}
	if (a->x > b->x)
		px_coord_swap(a, b);
}
/**
 * @brief 
 * 
 * @param img_vars 
 * @param a 
 * @param b 
 * @note https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void	draw_colored_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_slope_property	slope;

	normalize_coords_bresenham(&a, &b, &slope);
	draw_colored_pixels_bresenham(img_vars, a, b, slope);
}
