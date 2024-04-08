/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_coord_ortho.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:28:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:31:48 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

/**
 * @brief Performs orthographic projection from world coordinates to screen
 *        coordinates.
 *
 * @param world_coord The world coordinate to be transformed.
 * @return The resulting screen coordinate after orthographic projection.
 * @note Both input and ouput points are stored in 4x1 matrices.
 */
t_mx	screen_coord_ortho(t_mx world_coord)
{
	t_mx	ortho_proj_2x4;

	ortho_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
	{1, 0, 0, 0},
	{0, 1, 0, 0}}};
	return (mxa_mult_mxb(ortho_proj_2x4, world_coord));
}
