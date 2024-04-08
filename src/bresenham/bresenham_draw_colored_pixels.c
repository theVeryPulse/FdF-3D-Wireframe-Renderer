/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_draw_colored_pixels.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:26:57 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:26:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "px_coord.h"
#include "img_vars.h"
#include "image.h"
#include "argb.h"
#include "libft.h"

static void
calc_error_and_delta(
	int *error, t_delta *delta, t_px_coord *a, t_px_coord *b);

static void
init_gradient_color_transition(
	t_transition *t, t_px_coord *a, t_px_coord *b);

static t_argb
gradient_color(
	double transition, t_argb start, t_argb end);

static void
bresenham_draw_colored_pixel(
	t_img_vars *img_vars, t_slope_property slope, t_px_coord point);

/**
 * @brief Draws colored pixels along a line using Bresenham's algorithm.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param a The starting point of the line.
 * @param b The ending point of the line.
 * @param slope Structure containing slope properties.
 */
void	bresenham_draw_colored_pixels(
	t_img_vars *img_vars, t_px_coord a, t_px_coord b, t_slope_property slope)
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
		bresenham_draw_colored_pixel(img_vars, slope, point);
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
 * @brief Calculates the error and delta values for Bresenham's line drawing
 *        algorithm.
 *
 * @param error Pointer to the error integer.
 * @param delta Pointer to the delta values structure.
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 */
static void	calc_error_and_delta(
	int *error, t_delta *delta, t_px_coord *a, t_px_coord *b)
{
	delta->x = ft_abs(b->x - a->x);
	delta->y = ft_abs(b->y - a->y);
	*error = 2 * delta->y - delta->x;
}

/**
 * @brief Initializes the transition value for gradient color interpolation.
 *
 * @param t Pointer to the transition structure.
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 */
static void	init_gradient_color_transition(
	t_transition *t, t_px_coord *a, t_px_coord *b)
{
	t->curr = 0.0;
	t->step = 1.0 / ft_abs(b->x - a->x);
}

/**
 * @brief Computes a gradient color between two ARGB colors based on the
 *        transition value.
 *
 * @param transition The transition value between the start and end colors
 *                   (0 to 1).
 * @param start The start color of the gradient.
 * @param end The end color of the gradient.
 * @return The gradient color.
 * @note The transition value determines the proportion of each color in the
 *       final gradient color. When t equals 0, returns 'start' color, when t
 *       equals 1, returns 'end' color
 */
static t_argb	gradient_color(double transition, t_argb start, t_argb end)
{
	t_argb	color;

	if (transition < 0 || transition > 1)
		return (start);
	color = argb(
			(0xff),
			((1 - transition) * get_r(start) + transition * get_r(end)),
			((1 - transition) * get_g(start) + transition * get_g(end)),
			((1 - transition) * get_b(start) + transition * get_b(end)));
	return (color);
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
static void	bresenham_draw_colored_pixel(
	t_img_vars *img_vars, t_slope_property slope, t_px_coord point)
{
	if (slope.is_greater_than_1 && slope.is_negative)
		image_put_pixel(img_vars, (t_px_coord){.x = point.y, .y = -point.x},
			point.color);
	else if (slope.is_negative)
		image_put_pixel(img_vars, (t_px_coord){.x = point.x, .y = -point.y},
			point.color);
	else if (slope.is_greater_than_1)
		image_put_pixel(img_vars, (t_px_coord){.x = point.y, .y = point.x},
			point.color);
	else
		image_put_pixel(img_vars, point, point.color);
}
