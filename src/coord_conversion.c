/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:39:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 00:52:19 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

t_px_coord	raster_coord(t_mx screen_coord)
{
	t_px_coord	raster_coord;

	raster_coord = mx_to_pxcoord(screen_coord);
	raster_coord.x = raster_coord.x + WIDTH / 2;
	raster_coord.y = -raster_coord.y + HEIGHT / 2;
	return (raster_coord);
}
