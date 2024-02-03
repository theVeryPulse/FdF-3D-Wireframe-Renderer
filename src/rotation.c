/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:35 by Philip            #+#    #+#             */
/*   Updated: 2024/02/03 23:22:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	round_int(double n)
{
	if (n > 0)
		return ((int)(n + 0.5));
	else
		return ((int)(n - 0.5));
}

t_matrix	mx_mult(t_matrix mxa, t_matrix mxb)
{
	t_matrix	product;
	int			i;
	float		entry;
	int			p_row_i;
	int			p_col_i;

	if (mxa.col_num != mxb.row_num)
		return ((t_matrix){0});
	product = (t_matrix){.row_num = mxa.row_num, .col_num = mxb.col_num};
	p_row_i = 0;
	while (p_row_i < product.row_num)
	{
		p_col_i = 0;
		entry = 0;
		while (p_col_i <product.col_num)
		{
			i = 0;
			while (i < mxa.col_num)
			{
				entry += mxa.entries[p_row_i][i] * mxb.entries[i][p_col_i];
				i++;
			}
			product.entries[p_row_i][p_col_i] = entry;
			p_col_i++;
		}
		p_row_i++;
	}
	return (product);
}

t_px_coord	xwin_coord(t_px_coord p_point)
{
	t_px_coord	result;

	result.x = p_point.x + WIDTH / 2;
	result.y = -p_point.y + HEIGHT / 2;
	ft_printf("P-system: (%d,%d), X-system: (%d,%d)\n", p_point.x, p_point.y, result.x, result.y);
	return (result);
}

t_matrix	pxcoord_to_mx(t_px_coord px_coord)
{
	t_matrix	mx;

	mx.col_num = 1;
	mx.row_num = 2;
	mx.entries[0][0] = (double)(px_coord.x);
	mx.entries[1][0] = (double)(px_coord.y);
	return (mx);
}

t_px_coord	mx_to_pxcoord(t_matrix mx)
{
	t_px_coord	px_coord;

	if (mx.col_num != 1 || mx.row_num != 2)
		return ((t_px_coord){0});
	px_coord.x = round(mx.entries[0][0]);
	px_coord.y = round(mx.entries[1][0]);
	return (px_coord);
}
