/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:53:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:58:43 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	point_real_coord(double x, double y, double z)
{
	t_mx	point;

	point = (t_mx){.row_num = 4, .col_num = 1, .entries = {{x}, {y}, {z}, {1}}};
	return (point);
}

t_mx	pxcoord_to_mx(t_px_coord px_coord)
{
	t_mx	mx;

	mx.col_num = 1;
	mx.row_num = 2;
	mx.entries[0][0] = (double)(px_coord.x);
	mx.entries[1][0] = (double)(px_coord.y);
	return (mx);
}

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
