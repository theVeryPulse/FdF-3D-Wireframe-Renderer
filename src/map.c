/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:23:31 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:37:02 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_vertex_color(t_vertex *vertex, char *str_color, size_t *i);

void	map_check(char *map_str)
{
	size_t	i;

	if (!map_str)
		exit(1);
	i = 0;
	while (map_str[i] && (ft_isspace(map_str[i]) || ft_isalnum(map_str[i])
			|| ft_strchr("+-,", map_str[i])))
	{
		i++;
	}
	if (map_str[i] != '\0')
	{
		free(map_str);
		exit(1);
	}
}

void	parse_map_data(t_map *map, char *str)
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

t_map	build_map(char *str)
{
	t_map	map;
	size_t	i;

	map.row_num = count_rows(str);
	map.col_num = count_cols(str);
	map.vertexes = (t_vertex *)ft_calloc(map.col_num * map.row_num,
			sizeof(t_vertex));
	if (!map.vertexes)
	{
		free(str);
		exit(1);
	}
	parse_map_data(&map, str);
	return (map);
}

void	populate_vertexes_in_map(t_vars *vars)
{
	int			col;
	int			row;
	int			i;
	double		init_scale;
	t_vertex	*vertex;

	init_scale = 50.0;
	row = 0;
	i = 0;
	while (row < vars->map.row_num)
	{
		col = 0;
		while (col < vars->map.col_num)
		{
			vertex = &(vars->map.vertexes[col + row * vars->map.col_num]);
			vertex->real_coord = point_real_coord(
					init_scale * col,
					init_scale * vertex->height,
					-init_scale * (vars->map.row_num - row - 1));
			col++;
		}
		row++;
	}
}

static void	get_vertex_color(t_vertex *vertex, char *str_color, size_t *i)
{
	if (*str_color == ',')
	{
		vertex->color = hexa_atoi(str_color + 1);
		(*i)++;
	}
	else
		vertex->color = WHITE;
}
