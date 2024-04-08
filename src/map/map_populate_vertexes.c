/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_populate_vertexes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:29:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:34:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static t_mx	point_real_coord(double x, double y, double z);

/**
 * @brief Populates the vertexes in the map structure with real coordinates.
 *
 * @param vars Pointer to the variables structure containing the map.
 * @note System have x,y on screen plane and z pointing outwards. The map is
 *       initialized that rows are parallel to x axis, and columns parallel to z
 *       axis, and height in y axis direction.
 */
void	map_populate_vertexes(t_map *map)
{
	int			col;
	int			row;
	int			i;
	double		init_scale;
	t_vertex	*vertex;

	init_scale = 50.0;
	row = 0;
	i = 0;
	while (row < map->row_num)
	{
		col = 0;
		while (col < map->col_num)
		{
			vertex = &(map->vertexes[col + row * map->col_num]);
			vertex->real_coord = point_real_coord(
					init_scale * col,
					init_scale * vertex->height,
					-init_scale * (map->row_num - row - 1));
			col++;
		}
		row++;
	}
}

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
static t_mx	point_real_coord(double x, double y, double z)
{
	t_mx	point;

	point = (t_mx){.row_num = 4, .col_num = 1, .entries = {{x}, {y}, {z}, {1}}};
	return (point);
}
