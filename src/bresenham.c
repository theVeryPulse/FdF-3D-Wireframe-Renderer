/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:22:37 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:45:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_colored_pixels_bresenham(t_img_vars *img_vars, t_px_coord a,
				t_px_coord b, t_slope_property slope);
static void	normalize_coords_bresenham(t_px_coord *a, t_px_coord *b,
				t_slope_property *slope);
static void	draw_pixel_bresenham(t_img_vars *img_vars, t_slope_property slope,
				t_px_coord point);

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

static void	normalize_coords_bresenham(t_px_coord *a, t_px_coord *b,
		t_slope_property *slope)
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

static void	draw_colored_pixels_bresenham(t_img_vars *img_vars,
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

static void	draw_pixel_bresenham(t_img_vars *img_vars, t_slope_property slope,
		t_px_coord point)
{
	if (!img_vars)
		return ;
	if (slope.is_greater_than_1 && slope.is_negative)
		put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x},
			point.color);
	else if (slope.is_negative)
		put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y},
			point.color);
	else if (slope.is_greater_than_1)
		put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x},
			point.color);
	else
		put_pixel_img(img_vars, point, point.color);
}
