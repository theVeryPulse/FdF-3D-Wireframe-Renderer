/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:35:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:23:10 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if 0
#include "fdf.h"

/**
 * @brief Counts the number of rows in the map data string.
 *
 * @param str The map data string.
 * @return The number of rows in the data.
 */
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

/**
 * @brief Counts the number of columns in the map data string.
 *
 * @param str The map data string.
 * @return The number of columns in the data.
 */
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

/**
 * @brief Skips over the current number in the map data string.
 *
 * @param str The map data string.
 * @param i Pointer to the current index in the string.
 */
void	skip_the_number(char *str, size_t *i)
{
	if (!str || !i)
		return ;
	while (ft_isdigit(str[*i]) || ft_strchr("+-", str[*i]))
		(*i)++;
}

/**
 * @brief Skips over the current hexadecimal number in the string.
 *
 * @param str The map data string.
 * @param i Pointer to the current index in the string.
 */
void	skip_the_hexa(char *str, size_t *i)
{
	while (ft_isalnum(str[*i]))
		(*i)++;
}

/**
 * @brief Set counter to the first column of the next row.
 *
 * @param num Pointer to the structure containing row and column numbers.
 */
void	next_row_first_col(t_num *num)
{
	num->row++;
	num->col = 1;
}
#endif
