/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 02:18:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_px_coord	ortho_raster_coord_with_color(t_vars *vars, int row_idx,
						int col_idx);
static t_px_coord	caval_raster_coord_with_color(t_vars *vars, int row_idx,
						int col_idx);

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

static t_px_coord	ortho_raster_coord_with_color(t_vars *vars, int row_idx,
			int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(ortho_screen_coord(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}

static t_px_coord	caval_raster_coord_with_color(t_vars *vars, int row_idx,
			int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(caval_screen_coord(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}
