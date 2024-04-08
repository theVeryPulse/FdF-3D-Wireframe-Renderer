/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:11:23 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 19:08:01 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Creates a 4x4 scaling matrix based on the given scaling factor.
 *
 * @param scaling The scaling factor to be applied uniformly along all axes.
 * @return The resulting 4x4 scaling matrix.
 */
// t_mx	get_scale4x4(double scaling)
// {
// 	t_mx	scale4x4;

// 	scale4x4 = (t_mx){
// 		.row_num = 4,
// 		.col_num = 4,
// 		.entries = {
// 	{scaling, 0, 0, 0},
// 	{0, scaling, 0, 0},
// 	{0, 0, scaling, 0},
// 	{0, 0, 0, 1}}};
// 	return (scale4x4);
// }

/**
 * @brief Creates a 4x4 rotation matrix which rotates the model to isometric
 *        angle.
 *
 * @return The rotation matrix for isometric projection angle.
 */
t_mx	isometric4x4(void)
{
	t_mx	iso_proj;

	iso_proj = mxa_mult_mxb(rot_x_mx_4x4(35.264 * PI / 180),
			rot_y_mx_4x4(-45 * PI / 180));
	return (iso_proj);
}
