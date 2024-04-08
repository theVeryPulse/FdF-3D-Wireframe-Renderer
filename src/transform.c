/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:07:22 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:39:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Transforms all vertexes using the given transformation matrix.
 *
 * @param vertexes Array of vertexes to be transformed.
 * @param total The total number of vertexes in the array.
 * @param transform The transformation matrix.
 */
void	transform_all_vertexes(t_vertex *vertexes, int total, t_mx transform)
{
	int	i;

	i = 0;
	while (i < total)
	{
		vertexes[i].real_coord = mxa_mult_mxb(transform,
				vertexes[i].real_coord);
		i++;
	}
}
