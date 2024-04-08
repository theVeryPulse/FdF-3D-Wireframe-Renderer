/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raster_coord.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:29:50 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:33:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../px_coord.h"
#include "../matrix.h"
#include "../screen_size.h"

static t_px_coord	mx_to_pxcoord(t_mx mx);
static int	round_double(double n);

/**
 * @brief Converts screen coordinates to raster coordinates.
 *
 * @param screen_coord The screen coordinate matrix to be converted.
 * @return The resulting raster coordinate pixel coordinates after conversion.
 * @note the color value of returned coordinate structure is not set.
 */
t_px_coord	raster_coord(t_mx screen_coord)
{
	t_px_coord	raster_coord;

	raster_coord = mx_to_pxcoord(screen_coord);
	raster_coord.x = raster_coord.x + WIDTH / 2;
	raster_coord.y = -raster_coord.y + HEIGHT / 2;
	return (raster_coord);
}

/**
 * @brief Converts a matrix to a pixel coordinate.
 *
 * @param mx The matrix representing the pixel coordinate.
 * @return The resulting pixel coordinate.
 */
static t_px_coord	mx_to_pxcoord(t_mx mx)
{
	t_px_coord	px_coord;

	px_coord.x = round_double(mx.entries[0][0]);
	px_coord.y = round_double(mx.entries[1][0]);
	return (px_coord);
}

/**
 * @brief Rounds a double to the nearest integer.
 *
 * @param n The double value to be rounded.
 * @return The rounded integer value.
 * @note Relies on the C type casting.
 */
static int	round_double(double n)
{
	if (n > 0)
		return ((int)(n + 0.5));
	else
		return ((int)(n - 0.5));
}
