/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_rotation4x4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:53:07 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:54:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"
#include <math.h>

/**
 * @brief Generates a 4x4 matrix for rotation around the x-axis.
 *
 * @param angle The angle of rotation in radians.
 * @return The rotation matrix.
 */
t_mx	x_rotation4x4(double angle)
{
	t_mx	rot_x;

	rot_x = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{1, 0, 0, 0},
	{0, cos(angle), -sin(angle), 0},
	{0, sin(angle), cos(angle), 0},
	{0, 0, 0, 1}}};
	return (rot_x);
}
