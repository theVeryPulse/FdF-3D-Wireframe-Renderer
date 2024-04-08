/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_draw_colored_line.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:47:54 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:54:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham_internal.h"
#include "px_coord.h"
#include "scree_size.h"

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
void	bresenham_draw_colored_line(
	t_img_vars *img_vars, t_px_coord a, t_px_coord b)
{
	t_slope_property	slope;

	if ((a.x > WIDTH && b.x > WIDTH) || (a.y > HEIGHT && b.y > HEIGHT))
		return ;
	bresenham_normalize_coords(&a, &b, &slope);
	bresenham_draw_colored_pixels(img_vars, a, b, slope);
}
