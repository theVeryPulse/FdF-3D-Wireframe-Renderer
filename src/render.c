/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:41:18 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "bresenham/bresenham.h"
#include "coord_conversion/coord_conversion.h"

static t_px_coord	ortho_raster_coord_with_color(t_vars *vars, int row_idx,
						int col_idx);
static t_px_coord	caval_raster_coord_with_color(t_vars *vars, int row_idx,
						int col_idx);

/**
 * @brief Renders the colored orthographic model of the map on mlx image.
 *
 * @param vars A pointer to the variables structure.
 */
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
				bresenham_draw_colored_line(&vars->img_vars,
					ortho_raster_coord_with_color(vars, row_idx, col_idx),
					ortho_raster_coord_with_color(vars, row_idx, col_idx + 1));
			}
			if (row_idx != vars->map.row_num - 1)
			{
				bresenham_draw_colored_line(&vars->img_vars,
					ortho_raster_coord_with_color(vars, row_idx, col_idx),
					ortho_raster_coord_with_color(vars, row_idx + 1, col_idx));
			}
			col_idx++;
		}
		row_idx++;
	}
}

/**
 * @brief Renders the colored cavalier model of the map on mlx image.
 *
 * @param vars A pointer to the variables structure.
 */
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
				bresenham_draw_colored_line(&vars->img_vars,
					caval_raster_coord_with_color(vars, row_idx, col_idx),
					caval_raster_coord_with_color(vars, row_idx, col_idx + 1));
			}
			if (row_idx != vars->map.row_num - 1)
			{
				bresenham_draw_colored_line(&vars->img_vars,
					caval_raster_coord_with_color(vars, row_idx, col_idx),
					caval_raster_coord_with_color(vars, row_idx + 1, col_idx));
			}
			col_idx++;
		}
		row_idx++;
	}
}

/**
 * @brief Converts a vertex in the orthographic projection to a raster
 *        coordinate with color.
 *
 * @param vars A pointer to the variables structure.
 * @param row_idx The row index of the vertex in the map.
 * @param col_idx The column index of the vertex in the map.
 * @return The pixel coordinate with color.
 */
static t_px_coord	ortho_raster_coord_with_color(t_vars *vars, int row_idx,
			int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(screen_coord_ortho(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}

/**
 * @brief Converts a vertex in the cavalier projection to a raster coordinate
 *        with color.
 *
 * @param vars A pointer to the variables structure.
 * @param row_idx The row index of the vertex in the map.
 * @param col_idx The column index of the vertex in the map.
 * @return The pixel coordinate with color.
 */
static t_px_coord	caval_raster_coord_with_color(t_vars *vars, int row_idx,
			int col_idx)
{
	t_px_coord	pixel;
	t_vertex	vertex;

	vertex = vars->map.vertexes[col_idx + row_idx * vars->map.col_num];
	pixel = raster_coord(screen_coord_caval(vertex.real_coord));
	pixel.color = vertex.color;
	return (pixel);
}
