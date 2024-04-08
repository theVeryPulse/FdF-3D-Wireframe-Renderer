/**
 * @file bresenham_onefunction.c
 * @brief A one function version of the bresenham's line drawing algorithms,
 *        with comments showing which lines are refactored into which functions.
 */

#include "fdf.h"

static void	bresenham_draw_colored_pixels(t_img_vars *img_vars, t_px_coord a,
				t_px_coord b, t_slope_property slope);
static void	bresenham_normalize_coords(t_px_coord *a, t_px_coord *b,
				t_slope_property *slope);
static void	bresenham_draw_colored_pixel(t_img_vars *img_vars, t_slope_property slope,
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
void	bresenham_draw_colored_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_slope_property	slope;

	if ((a.x > WIDTH && b.x > WIDTH) || (a.y > HEIGHT && b.y > HEIGHT))
		return ;


// ==bresenham_normalize_coords(&a, &b, &slope);==
//    (Checks and records the slope properties)
	if (a.x > b.x)
		px_coord_swap(&a, &b);
	if ((a.x < b.x) && (a.y > b.y))
	{
		slope.is_negative = true;
		a.y *= -1;
		b.y *= -1;
	}
	else
		slope.is_negative = false;
	if (ft_abs(b.y - a.y) > ft_abs(b.x - a.x))
	{
		slope.is_greater_than_1 = true;
		int_swap(&(a.x), &(a.y));
		int_swap(&(b.x), &(b.y));
	}
	else
		slope.is_greater_than_1 = false;
	if (a.x > b.x)
		px_coord_swap(&a, &b);
// ==end==


// ==bresenham_draw_colored_pixels(img_vars, a, b, slope);==

// --calc_error_and_delta(&error, &delta, &a, &b);--
	t_px_coord		point;
	t_transition	t;
	int				error;
	t_delta			delta;

	delta.x = ft_abs(b.x - a.x);
	delta.y = ft_abs(b.y - a.y);
	error = 2 * delta.y - delta.x;
// --end--

// --init_gradient_color_transition(&t, &a, &b);--
	t.curr = 0.0;
	t.step = 1.0 / ft_abs(b.x - a.x);
	point = a;
// --end--

	while (point.x <= b.x)
	{
		point.color = gradient_color(t.curr, a.color, b.color);

// --bresenham_draw_colored_pixel(img_vars, slope, point);--
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
// --end--

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
// ==end==


}

/**
 * @brief Normalizes coordinates and determines slope properties for Bresenham's
 * line drawing algorithm.
 * 
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 * @param slope Pointer to the slope properties structure.
 * @note The bresenham_draw_colored_line function only works for lines in quadrant I with
 *       slope smaller than 1. Lines in all other quadrants are first converted
 *       to quadrant I, and mirrored along y=x if slope is greater than 1.
 */
static void	bresenham_normalize_coords(t_px_coord *a, t_px_coord *b,
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
static void	bresenham_draw_colored_pixels(t_img_vars *img_vars,
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
 * @brief Draws a colored pixel on the mlx image.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param slope Structure containing slope properties.
 * @param point The coordinates for drawing the colored pixel.
 * @note Draws a colored pixel on the mlx image, the original point coordinates
 *       are to be interpreted through the slope property.
 */
static void	bresenham_draw_colored_pixel(t_img_vars *img_vars, t_slope_property slope,
		t_px_coord point)
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

/**
 * @brief Calculates the error and delta values for Bresenham's line drawing
 *        algorithm.
 *
 * @param error Pointer to the error integer.
 * @param delta Pointer to the delta values structure.
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 */
void	calc_error_and_delta(int *error, t_delta *delta, t_px_coord *a,
		t_px_coord *b)
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
void	init_gradient_color_transition(t_transition *t, t_px_coord *a,
	t_px_coord *b)
{
	t->curr = 0.0;
	t->step = 1.0 / ft_abs(b->x - a->x);
}