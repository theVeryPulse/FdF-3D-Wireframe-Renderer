/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:53:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 16:43:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Creates a 4x1 matrix representing a point in real coordinates.
 *
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param z The z-coordinate of the point.
 * @return The resulting matrix representing the point in real coordinates.
 * @note Creates a 4x1 matrix representing a point in real coordinates
 *       (x, y, z). The homogeneous coordinate is set to 1 as per conventions in
 *       computer graphics.
 */
t_mx	point_real_coord(double x, double y, double z)
{
	t_mx	point;

	point = (t_mx){.row_num = 4, .col_num = 1, .entries = {{x}, {y}, {z}, {1}}};
	return (point);
}

/**
 * @brief Converts a pixel coordinate to a 2x1 matrix.
 *
 * @param px_coord The pixel coordinate to be converted.
 * @return The resulting matrix representing the pixel coordinate.
 */
t_mx	pxcoord_to_mx(t_px_coord px_coord)
{
	t_mx	mx;

	mx.col_num = 1;
	mx.row_num = 2;
	mx.entries[0][0] = (double)(px_coord.x);
	mx.entries[1][0] = (double)(px_coord.y);
	return (mx);
}

/**
 * @brief Converts a matrix to a pixel coordinate.
 *
 * @param mx The matrix representing the pixel coordinate.
 * @return The resulting pixel coordinate.
 */
t_px_coord	mx_to_pxcoord(t_mx mx)
{
	t_px_coord	px_coord;

	px_coord.x = round_double(mx.entries[0][0]);
	px_coord.y = round_double(mx.entries[1][0]);
	return (px_coord);
}

/* void	print_map(t_map *map)
{
	for (size_t i = 0; i < map->row_num; i++)
	{
		for (size_t j = 0; j < map->col_num; j++)
		{
			printf("%x ", map->vertexes[map->col_num * i + j].color);
		}
		printf("\n");
	}
} */
