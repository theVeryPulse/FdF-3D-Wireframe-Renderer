/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale4x4_for_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:48:24 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:48:45 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"
#include <X11/keysym.h>

/**
 * @brief Builds a 4x4 scaling matrix based on the pressed key.
 *
 * @param key The key for the scaling direction.
 * @return 4x4 scaling matrix.
 */
t_mx	scale4x4_for_key(int key)
{
	t_mx	scale4x4;
	double	scaling;

	scaling = 1;
	if (key == XK_i)
		scaling = 1.05;
	else if (key == XK_o)
		scaling = 0.95;
	scale4x4 = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{scaling, 0, 0, 0},
	{0, scaling, 0, 0},
	{0, 0, scaling, 0},
	{0, 0, 0, 1}}};
	return (scale4x4);
}
