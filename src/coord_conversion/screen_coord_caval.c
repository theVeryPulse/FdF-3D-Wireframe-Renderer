/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_coord_caval.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:33:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:34:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"

/**
 * @brief Performs cavalier projection from world coordinates to screen
 *        coordinates.
 *
 * @param world_coord The world coordinate matrix to be transformed.
 * @return The resulting screen coordinate matrix after cavalier projection.
 * @note Both input and ouput points are stored in 4x1 matrices.
 */
t_mx	screen_coord_caval(t_mx world_coord)
{
	t_mx	caval_proj_2x4;

	caval_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
	{1, 0, -0.2626609944 * 2, 0},
	{0, 1, -0.4254517622 * 2, 0}}};
	return (mxa_mult_mxb(caval_proj_2x4, world_coord));
}
