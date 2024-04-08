/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_rotation4x4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:53:58 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:54:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"
#include <math.h>

/**
 * @brief Generates a 4x4 matrix for rotation around the y-axis.
 *
 * @param angle The angle of rotation in radians.
 * @return The rotation matrix.
 */
t_mx	y_rotation4x4(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{cos(angle), 0, sin(angle), 0},
	{0, 1, 0, 0},
	{-sin(angle), 0, cos(angle), 0},
	{0, 0, 0, 1}}};
	return (rot_y);
}
