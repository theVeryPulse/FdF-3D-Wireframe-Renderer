/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:21:55 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/* Refactored */

# include "matrix.h"
# include "px_coord.h"
# include "argb.h"
# include "img_vars.h"
# include "map/map.h"

// # include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
// # include <fcntl.h>
// # include <math.h>
// # include <stdarg.h>
// # include <stdbool.h>
// # include <stddef.h>
// # include <stdlib.h>
// # include <sys/stat.h>
// # include <X11/keysym.h>
// # include <X11/X.h>

// # define WIDTH (1920)
// # define HEIGHT (1080)
// # define MAX_COL (4)
// # define MAX_ROW (4)
// # define BLACK (0x000000)
// # define WHITE (0xffffff)
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KWHT "\x1B[37m"

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_vars	img_vars;
	t_map		map;
}	t_vars;

/* Image manipulation */

void			change_screen_color(t_vars *vars, int color);
void			put_image_to_window_vars(t_vars *vars);
void			image_put_pixel(t_img_vars *img_vars, t_px_coord coord,
					t_argb color);

/* Transformation (generic) */

void			transform_all_vertexes(t_vertex *vertexes, int total,
					t_mx transform);

/* Render */

void			render_colored_caval_model(t_vars *vars);
void			render_colored_ortho_model(t_vars *vars);

/* Key Hook */

int				press_key_hook(t_win_list *win, int (*funct)(), void *param);

// void			print_map(t_map *map);

#endif