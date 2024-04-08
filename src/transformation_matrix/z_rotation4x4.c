/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_rotation4x4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:54:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:54:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"
#include <math.h>

/**
 * @brief Generates a 4x4 matrix for rotation around the z-axis.
 *
 * @param angle The angle of rotation in radians.
 * @return The rotation matrix.
 */
t_mx	z_rotation4x4(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{cos(angle), -sin(angle), 0, 0},
	{sin(angle), cos(angle), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	return (rot_z);
}
