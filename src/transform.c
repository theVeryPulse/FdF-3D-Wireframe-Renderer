/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 21:07:22 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:18:50 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	build_translation_matrix_for_key(int key)
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

t_mx	build_scale_matrix_for_key(int key)
{
	t_mx	scale4x4;

	if (key == XK_i)
		scale4x4 = get_scale4x4(1.1);
	else if (key == XK_o)
		scale4x4 = get_scale4x4(0.9);
	return (scale4x4);
}

t_mx	build_rotation_matrix_for_key(int key)
{
	t_mx	rotate4x4;

	if (key == XK_e)
		rotate4x4 = rot_y_mx_4x4(10.0 * PI / 180.0);
	else if (key == XK_q)
		rotate4x4 = rot_y_mx_4x4(-10.0 * PI / 180.0);
	else if (key == XK_s)
		rotate4x4 = rot_x_mx_4x4(10.0 * PI / 180.0);
	else if (key == XK_w)
		rotate4x4 = rot_x_mx_4x4(-10.0 * PI / 180.0);
	else if (key == XK_a)
		rotate4x4 = rot_z_mx_4x4(10.0 * PI / 180.0);
	else if (key == XK_d)
		rotate4x4 = rot_z_mx_4x4(-10.0 * PI / 180.0);
	return (rotate4x4);
}

void	transform_all_vertexes(t_vertex *vertexes, int total, t_mx transform)
{
	int	i;

	i = 0;
	while (i < total)
	{
		vertexes[i].real_coord = mxa_mult_mxb(transform,
				vertexes[i].real_coord);
		i++;
	}
}
