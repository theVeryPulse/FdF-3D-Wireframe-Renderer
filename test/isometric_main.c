/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:09 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 21:04:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	translation_mx(void)
{
	t_mx	mx;

	mx = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {
			{1, 0, 0, 500},
			{0, 1, 0, 100},
			{0, 0, 1, 100},
			{0, 0, 0, 1},
		}
	};
	return (mx);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	char		*content;
	t_map		map;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Rotating Cube");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	double angle1;
	t_mx	rot_4x4;
	
	angle1 = 0;
	rot_4x4 = rot_x_mx_4x4(angle1);
	t_mx	projection_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
			{1, 0, 0, 0},
			{0, 1, 0, 0}
		}
	};

	// Orthographic Projection =================================================
	t_mx	a_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{-200}, {200}, {200}, {1}}};
	t_mx	b_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{200}, {200}, {200}, {1}}};
	t_mx	c_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{200}, {-200}, {200}, {1}}};
	t_mx	d_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{-200}, {-200}, {200}, {1}}};
	t_mx	e_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{-200}, {200}, {-200}, {1}}};
	t_mx	f_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{200}, {200}, {-200}, {1}}};
	t_mx	g_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{200}, {-200}, {-200}, {1}}};
	t_mx	h_4x1 = (t_mx){.row_num = 4, .col_num = 1, .entries = {{-200}, {-200}, {-200}, {1}}};
	while (1)
	{
		t_px_coord	a1 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, a_4x1)));
		t_px_coord	b1 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, b_4x1)));
		t_px_coord	c1 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, c_4x1)));
		t_px_coord	d1 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, d_4x1)));
		t_px_coord	a2 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, e_4x1)));
		t_px_coord	b2 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, f_4x1)));
		t_px_coord	c2 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, g_4x1)));
		t_px_coord	d2 = mx_to_pxcoord((mx_mult(3, projection_2x4, rot_4x4, h_4x1)));
		fill_image_with_color(&vars.img_vars, BLACK);

		draw_line(&vars.img_vars, raster_coord(a1), raster_coord(b1), WHITE);
		draw_line(&vars.img_vars, raster_coord(b1), raster_coord(c1), WHITE);
		draw_line(&vars.img_vars, raster_coord(c1), raster_coord(d1), WHITE);
		draw_line(&vars.img_vars, raster_coord(d1), raster_coord(a1), WHITE);

		draw_line(&vars.img_vars, raster_coord(a2), raster_coord(b2), WHITE);
		draw_line(&vars.img_vars, raster_coord(b2), raster_coord(c2), WHITE);
		draw_line(&vars.img_vars, raster_coord(c2), raster_coord(d2), WHITE);
		draw_line(&vars.img_vars, raster_coord(d2), raster_coord(a2), WHITE);

		draw_line(&vars.img_vars, raster_coord(a1), raster_coord(a2), WHITE);
		draw_line(&vars.img_vars, raster_coord(b1), raster_coord(b2), WHITE);
		draw_line(&vars.img_vars, raster_coord(c1), raster_coord(c2), WHITE);
		draw_line(&vars.img_vars, raster_coord(d1), raster_coord(d2), WHITE);

		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

		// These two lines for rotating isometric
		angle1 += 1 * PI / 180;
		rot_4x4 = mx_mult(4, translation_mx(), rot_y_mx_4x4(angle1) ,rot_x_mx_4x4(35.264 * PI/ 180), rot_y_mx_4x4(45 * PI / 180));

		// This line for stationary isometric
		// rot_4x4 = mx_mult(4, translation_mx(), ,rot_x_mx_4x4(35.264 * PI/ 180), rot_y_mx_4x4(45 * PI / 180));
	}

	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	mlx_loop(vars.mlx_ptr);
}