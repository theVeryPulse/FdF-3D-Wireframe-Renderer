/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/02/04 22:13:58 by Philip           ###   ########.fr       */
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
# define MAX_COL (10)
# define MAX_ROW (10)
# define BLACK (0x0)
# define WHITE (0xffffff)
# define PI (3.1415926)

typedef int t_unit;
typedef int t_pixel;
typedef int t_color;

typedef struct	s_3d_af_vector
{
	double			x;
	double			y;
	double			z;
	const double	w;
}	t_3d_af_vector;

typedef struct	s_matrix
{
	int		row_num;
	int		col_num;
	double	entries[MAX_ROW][MAX_COL];
}	t_mx;


typedef struct	s_img_vars
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img_vars;

typedef struct	s_px_coord
{
	t_pixel	x;
	t_pixel	y;
}	t_px_coord;

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

t_map		build_map(char *str);
void		change_screen_color(t_vars *vars, int color);
int			create_argb(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha);
int			destroy_exit(t_vars *vars);
void		ensure_eol(t_list *last);
void		fill_image_with_color(t_img_vars *img_vars, int color);
void		fill_points(t_map *map, char *str);
int			handle_key(int key, t_vars *vars);
int			hexa_to_int(const char *str);
void		map_check(char *map_str);
void		mouse_button(int button,int x,int y, void *p);
int			mouse_motion(int x,int y, void *p);
t_px_coord	mx_to_pxcoord(t_mx mx);
void		put_pixel_img(t_img_vars *img_vars, t_px_coord coord, t_color color);
t_mx		pxcoord_to_mx(t_px_coord px_coord);
char		*read_file(const char *file);
t_px_coord	xwin_coord(t_px_coord p_point);

/* Line drawing */

void		draw_diagonal_line(t_img_vars *image, t_px_coord start, t_px_coord end, int color);
void		draw_grid_line(t_img_vars *img_vars, t_px_coord start, t_px_coord end, int color);
void		draw_line(t_img_vars *img_vars, t_px_coord start, t_px_coord end, int color);

/* Matrix */

t_mx		mxa_mult_mxb(t_mx mxa, t_mx mxb);
t_mx		mx_mult(int mx_count, ...);
t_mx		psp_proj_mx(double distance, double z);
t_mx		rot_x_mx(double angle);
t_mx		rot_y_mx(double angle);
t_mx		rot_z_mx(double angle);


#endif