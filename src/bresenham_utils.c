/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:25:40 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 19:53:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if 0
#include "fdf.h"
#include "bresenham.h"
#include "argb.h"

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
t_argb	gradient_color(double transition, t_argb start, t_argb end)
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
#endif
