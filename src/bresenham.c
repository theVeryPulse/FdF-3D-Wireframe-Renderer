/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:22:37 by Philip            #+#    #+#             */
/*   Updated: 2024/03/28 15:56:30 by Philip           ###   ########.fr       */
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
 * @brief Draws a colored line between two points on the mlx image
 *
 * @param img_vars Pointer to the image variables structure.
 * @param a The starting point of the line.
 * @param b The ending point of the line.
 * @note Draws a line between the points 'a' and 'b' on the screen using and
 *       colors each pixel along the line based on gradient color interpolation
 *       between the colors of 'a' and 'b'.
 *       Coordinates are in screen system (between 0 and window size)
 * @see Bresenham's algorithm: 
 *      https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 */
void	draw_colored_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_slope_property	slope;

	if ((a.x > WIDTH && b.x > WIDTH) || (a.y > HEIGHT && b.y > HEIGHT))
		return ;
	normalize_coords_bresenham(&a, &b, &slope);
	draw_colored_pixels_bresenham(img_vars, a, b, slope);
}

/**
 * @brief Normalizes coordinates and determines slope properties for Bresenham's
 * line drawing algorithm.
 * 
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 * @param slope Pointer to the slope properties structure.
 * @note The draw_colored_line function only works for lines in quadrant I with
 *       slope smaller than 1. Lines in all other quadrants are first converted
 *       to quadrant I, and mirrored along y=x if slope is greater than 1.
 */
static void	normalize_coords_bresenham(t_px_coord *a, t_px_coord *b,
		t_slope_property *slope)
{
	if (a->x > b->x)
		px_coord_swap(a, b);
	if ((a->x < b->x) && (a->y > b->y))
	{
		slope->is_negative = true;
		a->y *= -1;
		b->y *= -1;
	}
	else
		slope->is_negative = false;
	if (ft_abs(b->y - a->y) > ft_abs(b->x - a->x))
	{
		slope->is_greater_than_1 = true;
		int_swap(&(a->x), &(a->y));
		int_swap(&(b->x), &(b->y));
	}
	else
		slope->is_greater_than_1 = false;
	if (a->x > b->x)
		px_coord_swap(a, b);
}

/**
 * @brief Draws colored pixels along a line using Bresenham's algorithm.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param a The starting point of the line.
 * @param b The ending point of the line.
 * @param slope Structure containing slope properties.
 */
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
	init_gradient_color_transition(&t, &a, &b);
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

/**
 * @brief Draws a colored pixel on the mlx image.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param slope Structure containing slope properties.
 * @param point The coordinates for drawing the colored pixel.
 * @note Draws a colored pixel on the mlx image, the original point coordinates
 *       are to be interpreted through the slope property.
 */
static void	draw_pixel_bresenham(t_img_vars *img_vars, t_slope_property slope,
		t_px_coord point)
{
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
