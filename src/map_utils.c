/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:35:10 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 00:36:27 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_rows(char *str)
{
	size_t	i;
	int		row_num;

	i = 0;
	row_num = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			row_num++;
		i++;
	}
	return (row_num);
}

int	count_cols(char *str)
{
	size_t	i;
	int		col_num;

	i = 0;
	col_num = 0;
	while (str[i] && str[i] != '\n')
	{
		if (ft_isdigit(str[i]) || ft_strchr("+-", str[i]))
			col_num++;
		while (ft_isalnum(str[i]) || ft_strchr("+-,x", str[i]))
			i++;
		while (str[i] == ' ')
			i++;
	}
	return (col_num);
}

void	skip_the_number(char *str, size_t *i)
{
	if (!str || !i)
		return ;
	while (ft_isdigit(str[*i]) || ft_strchr("+-", str[*i]))
		(*i)++;
}

void	skip_the_hexa(char *str, size_t *i)
{
	while (ft_isalnum(str[*i]))
		(*i)++;
}

void	next_row_first_col(t_num *num)
{
	num->row++;
	num->col = 1;
}
