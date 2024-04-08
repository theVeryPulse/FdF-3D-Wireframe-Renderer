/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:20:18 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:30:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static int	count_rows(char *map_str);
static int	count_cols(char *map_str);

/**
 * @brief Builds the map structure from the given map string.
 *
 * @param map Pointer to the map structure.
 * @param map_str The map string containing the map data.
 */
void	map_build(t_map *map, char *map_str)
{
	size_t	i;

	map->row_num = count_rows(map_str);
	map->col_num = count_cols(map_str);
	map->vertexes = (t_vertex *)ft_calloc(
			map->col_num * map->row_num, sizeof(t_vertex));
	if (!map->vertexes)
	{
		free(map_str);
		exit(1);
	}
	map_parse_data(map, map_str);
	map_populate_vertexes(map);
}

/**
 * @brief Counts the number of rows in the map data string.
 *
 * @param str The map data string.
 * @return The number of rows in the data.
 */
static int	count_rows(char *map_str)
{
	size_t	i;
	int		row_num;

	i = 0;
	row_num = 0;
	while (map_str[i])
	{
		if (map_str[i] == '\n')
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
static int	count_cols(char *map_str)
{
	size_t	i;
	int		col_num;

	i = 0;
	col_num = 0;
	while (map_str[i] && map_str[i] != '\n')
	{
		if (ft_isdigit(map_str[i]) || ft_strchr("+-", map_str[i]))
			col_num++;
		while (ft_isalnum(map_str[i]) || ft_strchr("+-,x", map_str[i]))
			i++;
		while (map_str[i] == ' ')
			i++;
	}
	return (col_num);
}
