/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:39:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 16:23:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Performs orthographic projection from world coordinates to screen
 *        coordinates.
 *
 * @param world_coord The world coordinate to be transformed.
 * @return The resulting screen coordinate after orthographic projection.
 * @note Both input and ouput points are stored in 4x1 matrices.
 */
t_mx	ortho_screen_coord(t_mx world_coord)
{
	t_mx	ortho_proj_2x4;

	ortho_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
	{1, 0, 0, 0},
	{0, 1, 0, 0}}};
	return (mxa_mult_mxb(ortho_proj_2x4, world_coord));
}

/**
 * @brief Performs cavalier projection from world coordinates to screen
 *        coordinates.
 *
 * @param world_coord The world coordinate matrix to be transformed.
 * @return The resulting screen coordinate matrix after cavalier projection.
 * @note Both input and ouput points are stored in 4x1 matrices.
 */
t_mx	caval_screen_coord(t_mx world_coord)
{
	t_mx	caval_proj_2x4;

	caval_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
	{1, 0, -0.2626609944 * 2, 0},
	{0, 1, -0.4254517622 * 2, 0}}};
	return (mxa_mult_mxb(caval_proj_2x4, world_coord));
}

/**
 * @brief Converts screen coordinates to raster coordinates.
 *
 * @param screen_coord The screen coordinate matrix to be converted.
 * @return The resulting raster coordinate pixel coordinates after conversion.
 * @note the color value of returned coordinate structure is not set.
 */
t_px_coord	raster_coord(t_mx screen_coord)
{
	t_px_coord	raster_coord;

	raster_coord = mx_to_pxcoord(screen_coord);
	raster_coord.x = raster_coord.x + WIDTH / 2;
	raster_coord.y = -raster_coord.y + HEIGHT / 2;
	return (raster_coord);
}
