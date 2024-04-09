/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation4x4_for_key.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:46:41 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:35:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../matrix.h"
#include <X11/keysym.h>

/**
 * @brief Builds a 4x4 translation matrix based on the pressed key.
 *
 * @param key The key for the translation direction.
 * @return 4x4 translation matrix.
 */
t_mx	translation4x4_for_key(int key)
{
	t_mx	transl4x4;

	transl4x4 = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{1, 0, 0, 0},
	{0, 1, 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	if (key == XK_Up)
		transl4x4.entries[1][3] = 10;
	else if (key == XK_Down)
		transl4x4.entries[1][3] = -10;
	else if (key == XK_Left)
		transl4x4.entries[0][3] = -10;
	else if (key == XK_Right)
		transl4x4.entries[0][3] = 10;
	return (transl4x4);
}
