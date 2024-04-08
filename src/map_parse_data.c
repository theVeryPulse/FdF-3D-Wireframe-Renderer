/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:10:19 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:31:04 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "argb.h"
#include "hex_atoi.h"
#include "libft.h"
#include <stddef.h>

static void	skip_the_number(char *str, size_t *i);
static void	skip_the_hexa(char *str, size_t *i);
static void	get_vertex_color(t_vertex *vertex, char *str_color, size_t *i);
static void	next_row_first_col(t_num *num);

/**
 * @brief Parses the map data from the string and populates the vertexes of the 
 *        map.
 *
 * @param map Pointer to the map structure to be populated.
 * @param str The string containing the map data.
 */
void	map_parse_data(t_map *map, char *str)
{
	size_t	i;
	size_t	vertex_idx;
	t_num	num;

	i = 0;
	vertex_idx = 0;
	num = (t_num){.row = 1, .col = 1};
	while (str[i])
	{
		if (ft_isdigit(str[i]) || ft_strchr("+-", str[i]))
		{
			map->vertexes[vertex_idx] = (t_vertex){.row = num.row,
				.col = num.col, .height = ft_atoi(str + i)};
			skip_the_number(str, &i);
			get_vertex_color(&(map->vertexes[vertex_idx]), &str[i], &i);
			skip_the_hexa(str, &i);
			vertex_idx++;
			num.col++;
		}
		if (str[i] == '\n')
			next_row_first_col(&num);
		i++;
	}
}

/**
 * @brief Retrieves the color of a vertex from the string and updates the
 *        vertex structure.
 *
 * @param vertex Pointer to the vertex structure.
 * @param str_color The  string containing the color.
 * @param i Pointer to the current index in the string.
 * @note Color string should be in format "0xRRGGBB"
 */
static void	get_vertex_color(t_vertex *vertex, char *str_color, size_t *i)
{
	if (*str_color == ',')
	{
		vertex->color = hex_atoi(str_color + 1);
		(*i)++;
	}
	else
		vertex->color = WHITE;
}

/**
 * @brief Skips over the current number in the map data string.
 *
 * @param str The map data string.
 * @param i Pointer to the current index in the string.
 */
static void	skip_the_number(char *str, size_t *i)
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
static void	skip_the_hexa(char *str, size_t *i)
{
	while (ft_isalnum(str[*i]))
		(*i)++;
}

/**
 * @brief Set counter to the first column of the next row.
 *
 * @param num Pointer to the structure containing row and column numbers.
 */
static void	next_row_first_col(t_num *num)
{
	num->row++;
	num->col = 1;
}
