/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:05:51 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:25:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdarg.h>

static void	mx_mult_error_msg(void);
static void	calc_mx_product(t_mx *product, t_mx *mxa, t_mx *mxb);

/**
 * @brief Transposes the given matrix.
 *
 * @param mx The matrix to be transposed.
 * @return The transposed matrix.
 */
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

/**
 * @brief Multiplies multiple matrices together.
 *
 * @param mx_count The number of matrices to multiply.
 * @param ... The matrices to multiply.
 * @return The product of the matrices.
 */
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

/**
 * @brief Multiplies two matrices.
 *
 * @param mxa The first matrix.
 * @param mxb The second matrix.
 * @return The product of the matrices.
 */
t_mx	mxa_mult_mxb(t_mx mxa, t_mx mxb)
{
	t_mx	product;
	int		i;
	double	entry;
	int		p_row_i;
	int		p_col_i;

	if (mxa.col_num != mxb.row_num)
	{
		mx_mult_error_msg();
		return ((t_mx){0});
	}
	product = (t_mx){.row_num = mxa.row_num, .col_num = mxb.col_num};
	calc_mx_product(&product, &mxa, &mxb);
	return (product);
}

/**
 * @brief Prints an error message for wrong number of rows and columns for
 *        multiplication.
 */
static void	mx_mult_error_msg(void)
{
	ft_dprintf(STDERR_FILENO,
		KRED"WARNING: "KNRM
		"Incorrect number of columns and rows for matrix multiplication\n");
}

/**
 * @brief Calculates the product of two matrices.
 *
 * @param product Pointer to the production matrix.
 * @param mxa Pointer to the first matrix.
 * @param mxb Pointer to the second matrix.
 */
static void	calc_mx_product(t_mx *product, t_mx *mxa, t_mx *mxb)
{
	int		i;
	int		p_row_i;
	int		p_col_i;
	double	entry;

	p_row_i = 0;
	while (p_row_i < product->row_num)
	{
		p_col_i = 0;
		while (p_col_i < product->col_num)
		{
			entry = 0;
			i = 0;
			while (i < mxa->col_num)
			{
				entry += mxa->entries[p_row_i][i] * mxb->entries[i][p_col_i];
				i++;
			}
			product->entries[p_row_i][p_col_i] = entry;
			p_col_i++;
		}
		p_row_i++;
	}
}
