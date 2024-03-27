/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:25:40 by Philip            #+#    #+#             */
/*   Updated: 2024/03/27 18:32:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
