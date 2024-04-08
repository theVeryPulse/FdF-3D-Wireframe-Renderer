/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:19:13 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:59:56 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Swaps the values of two integers.
 *
 * @param a Pointer to the first integer.
 * @param b Pointer to the second integer.
 */
void	int_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/**
 * @brief Swaps the values of two pixel coordinates.
 *
 * @param a Pointer to the first pixel coordinate.
 * @param b Pointer to the second pixel coordinate.
 */
void	px_coord_swap(t_px_coord *a, t_px_coord *b)
{
	t_px_coord	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

#if 0
/**
 * @brief Rounds a double to the nearest integer.
 *
 * @param n The double value to be rounded.
 * @return The rounded integer value.
 * @note Relies on the C type casting.
 */
int	round_double(double n)
{
	if (n > 0)
		return ((int)(n + 0.5));
	else
		return ((int)(n - 0.5));
}
#endif
