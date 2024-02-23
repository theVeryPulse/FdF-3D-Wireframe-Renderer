/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/02/23 16:24:35 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	ortho_screen_coord(t_mx world_coord)
{
	static const t_mx	ortho_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {{1, 0, 0, 0},
					{0, 1, 0, 0}}};
	return(mxa_mult_mxb(ortho_proj_2x4, world_coord));
}

t_px_coord	ortho_raster_coord_with_color(t_vars *vars, int row_idx, int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(ortho_screen_coord(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}

void	render_colored_ortho_model(t_vars *vars)
{
	int			row_idx;
	int			col_idx;

	row_idx = 0;
	while (row_idx < vars->map.row_num)
	{
		col_idx = 0;
		while (col_idx < vars->map.col_num)
		{
			if (col_idx != vars->map.col_num - 1)
			{
				draw_colored_line(&vars->img_vars, 
					ortho_raster_coord_with_color(vars, row_idx, col_idx), 
					ortho_raster_coord_with_color(vars, row_idx, col_idx + 1));
			}
			if (row_idx != vars->map.row_num - 1)
			{
				draw_colored_line(&vars->img_vars,
					ortho_raster_coord_with_color(vars, row_idx, col_idx),
					ortho_raster_coord_with_color(vars, row_idx + 1, col_idx));
			}
			col_idx++;
		}
		row_idx++;
	}
}

// 0.5 * cos(45 degrees) = 0.35355339059
t_mx	caval_screen_coord(t_mx world_coord)
{
	static const t_mx	caval_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {{1, 0, -0.2626609944 * 2, 0},
					{0, 1, -0.4254517622 * 2, 0}}};
	return(mxa_mult_mxb(caval_proj_2x4, world_coord));
}

t_px_coord	caval_raster_coord_with_color(t_vars *vars, int row_idx, int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(caval_screen_coord(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}

void	render_colored_caval_model(t_vars *vars)
{
	int			row_idx;
	int			col_idx;

	row_idx = 0;
	while (row_idx < vars->map.row_num)
	{
		col_idx = 0;
		while (col_idx < vars->map.col_num)
		{
			if (col_idx != vars->map.col_num - 1)
			{
				draw_colored_line(&vars->img_vars,
					caval_raster_coord_with_color(vars, row_idx, col_idx),
					caval_raster_coord_with_color(vars, row_idx, col_idx + 1));
			}
			if (row_idx != vars->map.row_num - 1)
			{
				draw_colored_line(&vars->img_vars,
					caval_raster_coord_with_color(vars, row_idx, col_idx),
					caval_raster_coord_with_color(vars, row_idx + 1, col_idx));
			}
			col_idx++;
		}
		row_idx++;
	}
}
