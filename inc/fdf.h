/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/03/27 18:33:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include <fcntl.h>
# include <math.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <X11/keysym.h>
# include <X11/X.h>

# define WIDTH (1920)
# define HEIGHT (1080)
# define MAX_COL (4)
# define MAX_ROW (4)
# define BLACK (0x000000)
# define WHITE (0xffffff)
# define PI (3.1415926)
# define KNRM "\x1B[0m"
# define KRED "\x1B[31m"
# define KWHT "\x1B[37m"

typedef int	t_argb;

typedef struct s_num
{
	int	row;
	int	col;
}	t_num;

typedef struct s_transition
{
	double	curr;
	double	step;
}	t_transition;

typedef struct s_slope_property
{
	bool	is_greater_than_1;
	bool	is_negative;
}	t_slope_property;

typedef struct s_delta
{
	int	x;
	int	y;
}	t_delta;

typedef struct s_matrix
{
	int		row_num;
	int		col_num;
	double	entries[MAX_ROW][MAX_COL];
}	t_mx;

typedef struct s_img_vars
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img_vars;

typedef struct s_px_coord
{
	int		x;
	int		y;
	t_argb	color;
}	t_px_coord;

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

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_vars	img_vars;
	t_map		map;
}	t_vars;

/* Read file */

char			*read_file(const char *file);
int				hexa_atoi(const char *str);

/* Image manipulation */

void			change_screen_color(t_vars *vars, int color);
void			fill_image_with_color(t_img_vars *img_vars, int color);
void			put_image_to_window_vars(t_vars *vars);
void			put_pixel_img(t_img_vars *img_vars, t_px_coord coord,
					t_argb color);

/* Map */

t_map			build_map(char *str);
int				count_cols(char *str);
int				count_rows(char *str);
void			map_check(char *map_str);
void			next_row_first_col(t_num *num);
void			parse_map_data(t_map *map, char *str);
void			populate_vertexes_in_map(t_vars *vars);
void			skip_the_hexa(char *str, size_t *i);
void			skip_the_number(char *str, size_t *i);

/* Color */

int				argb(unsigned char alpha, unsigned char r, unsigned char g,
					unsigned char b);
unsigned char	get_a(t_argb argb);
unsigned char	get_b(t_argb argb);
unsigned char	get_g(t_argb argb);
unsigned char	get_r(t_argb argb);
t_argb			gradient_color(double transition, t_argb start, t_argb end);

/* Line drawing */

void			calc_error_and_delta(int *error, t_delta *delta, t_px_coord *a,
					t_px_coord *b);
void			draw_colored_line(t_img_vars *img_vars, t_px_coord a,
					t_px_coord b);
void			init_gradient_color_transition(t_transition *t, t_px_coord *a,
					t_px_coord *b);

/* Matrix */

t_mx			mx_mult(int mx_count, ...);
t_mx			mx_transpose(t_mx mx);
t_mx			mxa_mult_mxb(t_mx mxa, t_mx mxb);

/* Transformation (generic) */

t_mx			build_rotation_matrix_for_key(int key);
t_mx			build_scale_matrix_for_key(int key);
t_mx			build_translation_matrix_for_key(int key);
t_mx			get_scale4x4(double scaling);
void			transform_all_vertexes(t_vertex *vertexes, int total,
					t_mx transform);

/* Rotation */

t_mx			rot_x_mx_4x4(double angle);
t_mx			rot_y_mx_4x4(double angle);
t_mx			rot_z_mx_4x4(double angle);

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

t_mx			caval_screen_coord(t_mx world_coord);
t_mx			ortho_screen_coord(t_mx world_coord);
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

/* Helpers */

void			int_swap(int *a, int *b);
void			px_coord_swap(t_px_coord *a, t_px_coord *b);
int				round_double(double n);

/* Others */

t_px_coord		mx_to_pxcoord(t_mx mx);
t_mx			point_real_coord(double x, double y, double z);
t_mx			pxcoord_to_mx(t_px_coord px_coord);

// void			print_map(t_map *map);

#endif