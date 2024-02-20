/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:09 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 21:04:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	char		*content;
	t_map		map;
	
	/* content = read_file("rotation.fdf"); 
	printf("Content as one string:\n%s", content);
	map_check(content);
	printf("Map checked\n");
	map = build_map(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num); */

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Rotating Cube");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	// ROTATING SQUARE BY 1 DEGREE
	/* double angle = -1 * PI / 180;
	t_mx rot = (t_mx){.row_num = 2, .col_num = 2,
		.entries= {
			{cos(angle), -sin(angle)},
			{sin(angle), cos(angle)}
		}
	};
	t_px_coord	a_p = (t_px_coord){.x = -200, .y = 200};
	t_px_coord	b_p = (t_px_coord){.x = 200, .y = 200};
	t_px_coord	c_p = (t_px_coord){.x = 200, .y = -200};
	t_px_coord	d_p = (t_px_coord){.x = -200, .y = -200};
	while (1)
	{
		a_p = mx_to_pxcoord(mx_mult(2, rot, pxcoord_to_mx(a_p)));
		b_p = mx_to_pxcoord(mx_mult(2, rot, pxcoord_to_mx(b_p)));
		c_p = mx_to_pxcoord(mx_mult(2, rot, pxcoord_to_mx(c_p)));
		d_p = mx_to_pxcoord(mx_mult(2, rot, pxcoord_to_mx(d_p)));
		fill_image_with_color(&vars.img_vars, BLACK);
		draw_line(&vars.img_vars, raster_coord(a_p), raster_coord(b_p), WHITE);
		draw_line(&vars.img_vars, raster_coord(b_p), raster_coord(c_p), WHITE);
		draw_line(&vars.img_vars, raster_coord(c_p), raster_coord(d_p), WHITE);
		draw_line(&vars.img_vars, raster_coord(d_p), raster_coord(a_p), WHITE);
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	} */

	// Projects the same coordinates from rotating angles
	double angle1;
	t_mx	rot_3x3;
	
	angle1 = 0;
	rot_3x3 = rot_x_mx(angle1);
	t_mx	projection_2x3 = (t_mx){
		.row_num = 2,
		.col_num = 3,
		.entries = {
			{1, 0, 0},
			{0, 1, 0}
		}
	};

	/* Perspective Projection ================================================*/
	t_mx	cube[8];
	cube[0] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {200}}};
	cube[1] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {200}}};
	cube[2] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {200}}};
	cube[3] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {200}}};
	cube[4] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {-200}}};
	cube[5] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {-200}}};
	cube[6] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {-200}}};
	cube[7] = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {-200}}};
	
	while (1)
	{
		t_mx	rotated[8];
		t_mx	projected[8];

		fill_image_with_color(&vars.img_vars, BLACK);

		for (int i = 0; i < 8; i++)
		{
			rotated[i] = mx_mult(2, rot_3x3, cube[i]);
		}

		for (int i = 0; i < 8; i++)
		{
			// projected[i] = mx_mult(2, projection_2x3, rotated[i]);
			projected[i] = mx_mult(2, psp_proj_mx(rotated[i]), rotated[i]);
		}

		for (int i = 0; i < 3; i++)
		{
			draw_line(&vars.img_vars, raster_coord((projected[i])), raster_coord((projected[i + 1])), WHITE);
			draw_line(&vars.img_vars, raster_coord((projected[i + 4])), raster_coord((projected[i + 5])), WHITE);
			draw_line(&vars.img_vars, raster_coord((projected[i])), raster_coord((projected[i + 4])), WHITE);
		}
		draw_line(&vars.img_vars, raster_coord((projected[0])), raster_coord((projected[3])), WHITE);
		draw_line(&vars.img_vars, raster_coord((projected[4])), raster_coord((projected[7])), WHITE);
		draw_line(&vars.img_vars, raster_coord((projected[3])), raster_coord((projected[7])), WHITE);

		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
		angle1 += 1 * PI / 180;
		// rot_3x3 = mx_mult(3, rot_y_mx(angle1), rot_x_mx(angle1), rot_z_mx(angle1));
		rot_3x3 = mx_mult(1, rot_y_mx(angle1));
	}

	// Orthographic Projection =================================================
	/* t_mx	a_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {-400}}};
	t_mx	b_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {-400}}};
	t_mx	c_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {-400}}};
	t_mx	d_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {-400}}};
	t_mx	e_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {-800}}};
	t_mx	f_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {-800}}};
	t_mx	g_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {-800}}};
	t_mx	h_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {-800}}};
	while (1)
	{
		t_px_coord	a1 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, a_3x1)));
		t_px_coord	b1 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, b_3x1)));
		t_px_coord	c1 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, c_3x1)));
		t_px_coord	d1 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, d_3x1)));
		t_px_coord	a2 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, e_3x1)));
		t_px_coord	b2 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, f_3x1)));
		t_px_coord	c2 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, g_3x1)));
		t_px_coord	d2 = mx_to_pxcoord((mx_mult(3, projection_2x3, rot_3x3, h_3x1)));
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
		angle1 += 1 * PI / 180;
		rot_3x3 = mx_mult(3, rot_x_mx(angle1 + 1), rot_y_mx(angle1 + 2) ,rot_z_mx(angle1));
		// rot_3x3 = rot_x_mx(angle1);
		// rot_3x3 = rot_z_mx(angle1);
	} */


	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	mlx_loop(vars.mlx_ptr);
}