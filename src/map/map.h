/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:11:03 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:22:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../matrix.h"
# include "../argb.h"

typedef struct s_num
{
	int	row;
	int	col;
}	t_num;

typedef struct s_vertex
{
	int		row;
	int		col;
	int		height;
	t_argb	color;
	t_mx	real_coord;
}	t_vertex;

/**
 * vertexes should be a dynamically allocated array of required size.
 */
typedef struct s_map
{
	t_vertex	*vertexes;
	int			col_num;
	int			row_num;
}	t_map;

/* External functions */

void	map_build(t_map *map, char *map_str);
void	map_check(char *map_str);

/* Internal functions */

void	map_parse_data(t_map *map, char *str);
void	map_populate_vertexes(t_map *map);

#endif