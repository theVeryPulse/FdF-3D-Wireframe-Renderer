/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/02/21 17:25:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	screen_coord_ortho(t_mx world_coord)
{
	static const t_mx	ortho_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {{1, 0, 0, 0},
					{0, 1, 0, 0}}};
	return(mxa_mult_mxb(ortho_proj_2x4, world_coord));
}

// 0.5 * cos(45 degrees) = 0.35355339059
t_mx	screen_coord_cavilier(t_mx world_coord)
{
	static const t_mx	cavilier_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {{1, 0, -0.2626609944 * 2, 0},
					{0, 1, -0.4254517622 * 2, 0}}};
	return(mxa_mult_mxb(cavilier_proj_2x4, world_coord));
}

void	render_ortho_model(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < vars->map.row_num)
	{
		j = 0;
		while (j < vars->map.col_num)
		{
			if (j != vars->map.col_num - 1)
			{
				draw_line(&vars->img_vars,
					raster_coord(screen_coord_ortho(vars->map.vertexes[j + i * vars->map.col_num].real_coord)),
					raster_coord(screen_coord_ortho(vars->map.vertexes[j + 1 + i * vars->map.col_num].real_coord)),
					WHITE);
			}
			if (i != vars->map.row_num - 1)
			{
				draw_line(&vars->img_vars,
					raster_coord(screen_coord_ortho(vars->map.vertexes[j + i * vars->map.col_num].real_coord)),
					raster_coord(screen_coord_ortho(vars->map.vertexes[j + (i + 1) * vars->map.col_num].real_coord)),
					WHITE);
			}
			j++;
		}
		i++;
	}
}

void	render_colored_ortho_model(t_vars *vars)
{
	int			i;
	int			j;
	t_px_coord	a;
	t_px_coord	b;

	i = 0;
	while (i < vars->map.row_num)
	{
		j = 0;
		while (j < vars->map.col_num)
		{
			a = raster_coord(screen_coord_ortho(vars->map.vertexes[j + i * vars->map.col_num].real_coord));
			a.color = vars->map.vertexes[j + i * vars->map.col_num].color;
			if (j != vars->map.col_num - 1)
			{
				b = raster_coord(screen_coord_ortho(vars->map.vertexes[j + 1 + i * vars->map.col_num].real_coord));
				b.color = vars->map.vertexes[j + 1 + i * vars->map.col_num].color;
				draw_colored_line(&vars->img_vars, a, b);
			}
			if (i != vars->map.row_num - 1)
			{
				b = raster_coord(screen_coord_ortho(vars->map.vertexes[j + (i + 1) * vars->map.col_num].real_coord));
				b.color = vars->map.vertexes[j + (i + 1) * vars->map.col_num].color;
				draw_colored_line(&vars->img_vars, a, b);
			}
			j++;
		}
		i++;
	}
}

void	render_colored_cavilier_model(t_vars *vars)
{
	int			i;
	int			j;
	t_px_coord	a;
	t_px_coord	b;

	i = 0;
	while (i < vars->map.row_num)
	{
		j = 0;
		while (j < vars->map.col_num)
		{
			a = raster_coord(screen_coord_cavilier(vars->map.vertexes[j + i * vars->map.col_num].real_coord));
			a.color = vars->map.vertexes[j + i * vars->map.col_num].color;
			if (j != vars->map.col_num - 1)
			{
				b = raster_coord(screen_coord_cavilier(vars->map.vertexes[j + 1 + i * vars->map.col_num].real_coord));
				b.color = vars->map.vertexes[j + 1 + i * vars->map.col_num].color;
				draw_colored_line(&vars->img_vars, a, b);
			}
			if (i != vars->map.row_num - 1)
			{
				b = raster_coord(screen_coord_cavilier(vars->map.vertexes[j + (i + 1) * vars->map.col_num].real_coord));
				b.color = vars->map.vertexes[j + (i + 1) * vars->map.col_num].color;
				draw_colored_line(&vars->img_vars, a, b);
			}
			j++;
		}
		i++;
	}
}
