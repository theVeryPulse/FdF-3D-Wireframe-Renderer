/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/01/30 22:28:50 by Philip           ###   ########.fr       */
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

typedef int t_unit;

typedef int t_color;

typedef struct	s_point
{
	t_unit	row;
	t_unit	col;
	t_unit	height;
	t_color	color;
}	t_point;

typedef struct	s_map
{
	t_point	*points;
	int		col_num;
	int		row_num;
}	t_map;

int	create_trgb(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b);

#endif