/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation4x4_for_key.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:49:11 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:56:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "../matrix.h"
#include <X11/keysym.h>
#include <math.h>

/**
 * @brief Builds a 4x4 rotation matrix based on the pressed key.
 *
 * @param key The key for the rotation direction.
 * @return 4x4 rotation matrix.
 */
t_mx	rotation4x4_for_key(int key)
{
	t_mx	rotate4x4;

	if (key == XK_e)
		rotate4x4 = y_rotation4x4(1.0 * M_PI / 180.0);
	else if (key == XK_q)
		rotate4x4 = y_rotation4x4(-1.0 * M_PI / 180.0);
	else if (key == XK_s)
		rotate4x4 = x_rotation4x4(1.0 * M_PI / 180.0);
	else if (key == XK_w)
		rotate4x4 = x_rotation4x4(-1.0 * M_PI / 180.0);
	else if (key == XK_a)
		rotate4x4 = z_rotation4x4(1.0 * M_PI / 180.0);
	else if (key == XK_d)
		rotate4x4 = z_rotation4x4(-1.0 * M_PI / 180.0);
	return (rotate4x4);
}
