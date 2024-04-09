/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric4x4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:51:58 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:35:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "../matrix.h"
#include <math.h>

/**
 * @brief Creates a 4x4 rotation matrix which rotates the model to isometric
 *        angle.
 *
 * @return The rotation matrix for isometric projection angle.
 */
t_mx	isometric4x4(void)
{
	t_mx	iso_proj;

	iso_proj = mxa_mult_mxb(x_rotation4x4(35.264 * M_PI / 180),
			y_rotation4x4(-45 * M_PI / 180));
	return (iso_proj);
}
