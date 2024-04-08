/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_isometric.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:43:04 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:22:54 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Translates all vertexes of the orthographic model based on the pressed
 *        key.
 *
 * @param vars The pointer to the variables structure.
 * @param key The key for translation direction.
 */
void	translate(t_vars *vars, int key)
{
	t_mx	transl4x4;

	transl4x4 = build_translation_matrix_for_key(key);
	transform_all_vertexes(vars->map.vertexes,
		vars->map.row_num * vars->map.col_num,
		transl4x4);
	image_fill_color(&vars->img_vars, BLACK);
	render_colored_ortho_model(vars);
	put_image_to_window_vars(vars);
}

/**
 * @brief Scales all vertexes of the orthographic model based on the pressed 
 *        key.
 *
 * @param vars The pointer to the variables structure.
 * @param key The key for the scaling direction.
 */
void	scale(t_vars *vars, int key)
{
	t_mx	scale4x4;

	scale4x4 = build_scale_matrix_for_key(key);
	transform_all_vertexes(vars->map.vertexes,
		vars->map.row_num * vars->map.col_num,
		scale4x4);
	image_fill_color(&vars->img_vars, BLACK);
	render_colored_ortho_model(vars);
	put_image_to_window_vars(vars);
}

/**
 * @brief Rotates all vertexes of the orthographic model based on the given key.
 *
 * @param vars The pointer to the variables structure.
 * @param key The key for the rotation direction.
 */
void	rotate(t_vars *vars, int key)
{
	t_mx	rotate4x4;

	rotate4x4 = build_rotation_matrix_for_key(key);
	transform_all_vertexes(vars->map.vertexes,
		vars->map.row_num * vars->map.col_num,
		rotate4x4);
	image_fill_color(&vars->img_vars, BLACK);
	render_colored_ortho_model(vars);
	put_image_to_window_vars(vars);
}
