/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_normalize_coords.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:43:20 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:27:05 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "px_coord.h"
#include "libft.h"
#include <stdbool.h>

static void	px_coord_swap(t_px_coord *a, t_px_coord *b);
static void	int_swap(int *a, int *b);

/**
 * @brief Normalizes coordinates and determines slope properties for Bresenham's
 * line drawing algorithm.
 * 
 * @param a Pointer to the starting point of the line.
 * @param b Pointer to the ending point of the line.
 * @param slope Pointer to the slope properties structure.
 * @note The bresenham_draw_colored_line function only works for lines in 
 *       quadrant I with slope smaller than 1. Lines in all other quadrants are 
 *       first converted to quadrant I, and mirrored along y=x if slope is 
 *       greater than 1.
 */
void	bresenham_normalize_coords(
		t_px_coord *a, t_px_coord *b, t_slope_property *slope)
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
 * @brief Swaps the values of two pixel coordinates.
 *
 * @param a Pointer to the first pixel coordinate.
 * @param b Pointer to the second pixel coordinate.
 */
static void	px_coord_swap(t_px_coord *a, t_px_coord *b)
{
	t_px_coord	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Swaps the values of two integers.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
static void	int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
