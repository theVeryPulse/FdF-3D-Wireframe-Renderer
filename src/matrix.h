/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:27:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:28:42 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# define MAX_COL (4)
# define MAX_ROW (4)

typedef struct s_matrix
{
	int		row_num;
	int		col_num;
	double	entries[MAX_ROW][MAX_COL];
}	t_mx;

t_mx			mx_mult(int mx_count, ...);
t_mx			mxa_mult_mxb(t_mx mxa, t_mx mxb);
t_mx			mx_transpose(t_mx mx);

#endif
