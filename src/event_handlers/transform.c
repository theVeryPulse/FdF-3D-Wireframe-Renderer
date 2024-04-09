/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:07:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:37:28 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include "../transformation_matrix/transformation_matrix.h"
#include "../image.h"

void	transform(t_vars *vars, int key)
{
	t_mx	transform4x4;

	if (key == XK_Left || key == XK_Right
		|| key == XK_Up || key == XK_Down)
		transform4x4 = translation4x4_for_key(key);
	else if (key == XK_i || key == XK_o)
		transform4x4 = scale4x4_for_key(key);
	else if (key == XK_q || key == XK_e
		|| key == XK_w || key == XK_s
		|| key == XK_a || key == XK_d)
		transform4x4 = rotation4x4_for_key(key);
	else
		return ;
	transform_all_vertexes(vars->map.vertexes,
		vars->map.row_num * vars->map.col_num,
		transform4x4);
	image_fill_color(&vars->img_vars, BLACK);
	render_colored_ortho_model(vars);
	put_image_to_window_vars(vars);
}
