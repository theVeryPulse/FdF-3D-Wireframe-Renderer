/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:44:34 by Philip           ###   ########.fr       */
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

# include "libft.h"
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
void			image_fill_color(t_img_vars *img_vars, int color);
void			put_image_to_window_vars(t_vars *vars);
void			image_put_pixel(t_img_vars *img_vars, t_px_coord coord,
					t_argb color);

/* Transformation (generic) */

t_mx			rotation4x4_for_key(int key);
t_mx			scale4x4_for_key(int key);
t_mx			translation4x4_for_key(int key);
t_mx			get_scale4x4(double scaling);
void			transform_all_vertexes(t_vertex *vertexes, int total,
					t_mx transform);

/* Rotation */

t_mx			x_rotation4x4(double angle);
t_mx			y_rotation4x4(double angle);
t_mx			z_rotation4x4(double angle);

/* Transformation for isometric projection */

void			rotate(t_vars *vars, int key);
void			scale(t_vars *vars, int key);
void			translate(t_vars *vars, int key);

/* Transformation for cavalier projection */

void			scale_caval(t_vars *vars, int key);
void			translate_caval(t_vars *vars, int key);

/* Utility functions for transformation */

t_mx			get_scale4x4(double scaling);
t_mx			isometric4x4(void);

/* Coordinate transformation */

t_mx			screen_coord_caval(t_mx world_coord);
t_mx			screen_coord_ortho(t_mx world_coord);
t_px_coord		raster_coord(t_mx screen_coord);

/* Render */

void			render_colored_caval_model(t_vars *vars);
void			render_colored_ortho_model(t_vars *vars);

/* Key Hook */

int				press_key_hook(t_win_list *win, int (*funct)(), void *param);

/* Events */

int				caval_handle_key(int key, t_vars *vars);
int				destroy_exit(t_vars *vars);
int				isometric_handle_key(int key, t_vars *vars);
int				mouse_button(int button, int x, int y, void *p);
int				mouse_motion(int x, int y, void *p);

// void			print_map(t_map *map);

#endif