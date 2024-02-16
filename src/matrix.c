/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 22:05:51 by Philip            #+#    #+#             */
/*   Updated: 2024/02/13 22:10:30 by Philip           ###   ########.fr       */
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
