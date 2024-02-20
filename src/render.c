/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 22:22:18 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 23:45:43 by Philip           ###   ########.fr       */
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

void	render_colored_psp_model(t_vars *vars)
{
	int			i;
	int			j;
	t_mx		pt_a;
	t_mx		pt_b;
	t_px_coord	a;
	t_px_coord	b;

	i = 0;
	while (i < vars->map.row_num)
	{
		j = 0;
		while (j < vars->map.col_num)
		{
			pt_a = vars->map.vertexes[j + i * vars->map.col_num].real_coord;
			if (pt_a.entries[2][0] >= 0)
				continue ;
			t_mx	a_screen = screen_coord_ortho(pt_a);
			// TODO: left here
			a_screen.entries[0][0] /= round_double(fabs(pt_a.entries[2][0]));
			a_screen.entries[1][0] /= round_double(fabs(pt_a.entries[2][0]));
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
