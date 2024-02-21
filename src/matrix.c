/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:05:51 by Philip            #+#    #+#             */
/*   Updated: 2024/02/21 22:08:15 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	mx_transpose(t_mx mx)
{
	t_mx	mx_t;
	int		i;
	int		j;

	mx_t.col_num = mx.row_num;
	mx_t.row_num = mx.col_num;
	i = 0;
	while (i < MAX_ROW)
	{
		j = 0;
		while (j < MAX_COL)
		{
			mx_t.entries[i][j] = mx.entries[j][i];
			j++;
		}
		i++;
	}
	return (mx_t);
}

t_mx	mx_mult(int mx_count, ...)
{
	va_list	ap;
	t_mx	product;
	t_mx	next_mx;

	if (mx_count < 1)
		return ((t_mx){0});
	va_start(ap, mx_count);
	product = va_arg(ap, t_mx);
	while (mx_count > 1)
	{
		next_mx = va_arg(ap, t_mx);
		product = mxa_mult_mxb(product, next_mx);
		mx_count--;
	}
	va_end(ap);
	return (product);
}

t_mx	mxa_mult_mxb(t_mx mxa, t_mx mxb)
{
	t_mx	product;
	int		i;
	double	entry;
	int		p_row_i;
	int		p_col_i;

	if (mxa.col_num != mxb.row_num)
	{
		ft_putstr_fd(KRED, STDERR_FILENO);
		ft_putstr_fd("WARNING:", STDERR_FILENO);
		ft_putstr_fd(KWHT, STDERR_FILENO);
		ft_putendl_fd("Incorrect number of coloumns and rows for matrix "
			"multiplication", STDERR_FILENO);
		return ((t_mx){0});
	}
	product = (t_mx){.row_num = mxa.row_num, .col_num = mxb.col_num};
	p_row_i = 0;
	while (p_row_i < product.row_num)
	{
		p_col_i = 0;
		while (p_col_i <product.col_num)
		{
			entry = 0;
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
