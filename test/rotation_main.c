/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:09 by Philip            #+#    #+#             */
/*   Updated: 2024/02/04 22:57:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	char		*content;
	t_map		map;
	
	content = read_file("rotation.fdf"); 
	printf("Content as one string:\n%s", content);
	map_check(content);
	printf("Map checked\n");
	map = build_map(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

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
		draw_line(&vars.img_vars, xwin_coord(a_p), xwin_coord(b_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b_p), xwin_coord(c_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c_p), xwin_coord(d_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d_p), xwin_coord(a_p), WHITE);
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	} */

	// Projects the same coordinates from rotating angles
	double angle1;
	t_mx	rot_3x3;
	
	angle1 = 0;
	rot_3x3 = rot_x_mx(angle1);
	// rot_3x3 = rot_z_mx(angle1);
	t_mx	projection_2x3 = (t_mx){
		.row_num = 2,
		.col_num = 3,
		.entries = {
			{1, 0, 0},
			{0, 1, 0}
		}
	};
	t_mx	a_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {200}}};
	t_mx	b_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {200}}};
	t_mx	c_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {200}}};
	t_mx	d_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {200}}};
	t_mx	e_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {200}, {-200}}};
	t_mx	f_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {200}, {-200}}};
	t_mx	g_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{200}, {-200}, {-200}}};
	t_mx	h_3x1 = (t_mx){.row_num = 3, .col_num = 1, .entries = {{-200}, {-200}, {-200}}};

	/* Perspective Projection */ // TODO Needs debugging
	while (1)
	{
		fill_image_with_color(&vars.img_vars, BLACK);

		t_mx	rotated_a1 = (mx_mult(2, rot_3x3, a_3x1));
		t_mx	rotated_b1 = (mx_mult(2, rot_3x3, b_3x1));
		t_mx	rotated_c1 = (mx_mult(2, rot_3x3, c_3x1));
		t_mx	rotated_d1 = (mx_mult(2, rot_3x3, d_3x1));
		t_mx	rotated_a2 = (mx_mult(2, rot_3x3, e_3x1));
		t_mx	rotated_b2 = (mx_mult(2, rot_3x3, f_3x1));
		t_mx	rotated_c2 = (mx_mult(2, rot_3x3, g_3x1));
		t_mx	rotated_d2 = (mx_mult(2, rot_3x3, h_3x1));

		t_mx	projected_a1 = (mx_mult(2, psp_proj_mx((double)50, rotated_a1.entries[2][0]), rotated_a1));
		t_mx	projected_b1 = (mx_mult(2, psp_proj_mx((double)50, rotated_b1.entries[2][0]), rotated_b1));
		t_mx	projected_c1 = (mx_mult(2, psp_proj_mx((double)50, rotated_c1.entries[2][0]), rotated_c1));
		t_mx	projected_d1 = (mx_mult(2, psp_proj_mx((double)50, rotated_d1.entries[2][0]), rotated_d1));
		t_mx	projected_a2 = (mx_mult(2, psp_proj_mx((double)50, rotated_a2.entries[2][0]), rotated_a2));
		t_mx	projected_b2 = (mx_mult(2, psp_proj_mx((double)50, rotated_b2.entries[2][0]), rotated_b2));
		t_mx	projected_c2 = (mx_mult(2, psp_proj_mx((double)50, rotated_c2.entries[2][0]), rotated_c2));
		t_mx	projected_d2 = (mx_mult(2, psp_proj_mx((double)50, rotated_d2.entries[2][0]), rotated_d2));

		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_a1)), xwin_coord(mx_to_pxcoord(projected_b1)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_b1)), xwin_coord(mx_to_pxcoord(projected_c1)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_c1)), xwin_coord(mx_to_pxcoord(projected_d1)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_d1)), xwin_coord(mx_to_pxcoord(projected_a1)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_a1)), xwin_coord(mx_to_pxcoord(projected_a2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_b1)), xwin_coord(mx_to_pxcoord(projected_b2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_c1)), xwin_coord(mx_to_pxcoord(projected_c2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_d1)), xwin_coord(mx_to_pxcoord(projected_d2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_a2)), xwin_coord(mx_to_pxcoord(projected_b2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_b2)), xwin_coord(mx_to_pxcoord(projected_c2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_c2)), xwin_coord(mx_to_pxcoord(projected_d2)), WHITE);
		draw_line(&vars.img_vars, xwin_coord(mx_to_pxcoord(projected_d2)), xwin_coord(mx_to_pxcoord(projected_a2)), WHITE);


		/* draw_line(&vars.img_vars, xwin_coord(a1), xwin_coord(b1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b1), xwin_coord(c1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c1), xwin_coord(d1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d1), xwin_coord(a1), WHITE);

		draw_line(&vars.img_vars, xwin_coord(a2), xwin_coord(b2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b2), xwin_coord(c2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c2), xwin_coord(d2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d2), xwin_coord(a2), WHITE);

		draw_line(&vars.img_vars, xwin_coord(a1), xwin_coord(a2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b1), xwin_coord(b2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c1), xwin_coord(c2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d1), xwin_coord(d2), WHITE); */

		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
		angle1 += 1 * PI / 180;
		rot_3x3 = mx_mult(3, rot_x_mx(angle1 + 1), rot_y_mx(angle1 + 2) ,rot_z_mx(angle1));
		// rot_3x3 = rot_x_mx(angle1);
		// rot_3x3 = rot_z_mx(angle1);
	}

	// Orthographic Projection
	/* while (1)
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

		draw_line(&vars.img_vars, xwin_coord(a1), xwin_coord(b1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b1), xwin_coord(c1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c1), xwin_coord(d1), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d1), xwin_coord(a1), WHITE);

		draw_line(&vars.img_vars, xwin_coord(a2), xwin_coord(b2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b2), xwin_coord(c2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c2), xwin_coord(d2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d2), xwin_coord(a2), WHITE);

		draw_line(&vars.img_vars, xwin_coord(a1), xwin_coord(a2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b1), xwin_coord(b2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c1), xwin_coord(c2), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d1), xwin_coord(d2), WHITE);

		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
		angle1 += 1 * PI / 180;
		rot_3x3 = mx_mult(3, rot_x_mx(angle1 + 1), rot_y_mx(angle1 + 2) ,rot_z_mx(angle1));
		// rot_3x3 = rot_x_mx(angle1);
		// rot_3x3 = rot_z_mx(angle1);
	} */


	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	mlx_loop(vars.mlx_ptr);
}