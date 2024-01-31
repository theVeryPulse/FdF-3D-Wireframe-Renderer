/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/01/31 22:42:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH (1920)
# define HEIGHT (1080)

typedef int t_unit;
typedef int t_pixel;
typedef int t_color;

typedef struct	s_img_vars
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img_vars;

typedef struct	s_coord
{
	t_pixel	x;
	t_pixel	y;
}	t_coord;

typedef struct	s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_vars	img_vars;
}	t_vars;

typedef struct	s_vertex
{
	t_unit	row;
	t_unit	col;
	t_unit	height;
	t_color	color;
}	t_vertex;

typedef struct	s_map
{
	t_vertex	*vertexes;
	int			col_num;
	int			row_num;
}	t_map;

t_map	build_map(char *str);
int		create_argb(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
void	ensure_eol(t_list *last);
void	fill_points(t_map *map, char *str);
int		hexa_to_int(const char *str);
void	map_check(char *map_str);
char	*read_file(const char *file);

#endif