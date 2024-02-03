/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:09 by Philip            #+#    #+#             */
/*   Updated: 2024/02/03 23:22:38 by Philip           ###   ########.fr       */
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
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	double angle = -1 * PI / 180;
	t_matrix rotation = (t_matrix){.row_num = 2, .col_num = 2,
		.entries = {
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
		// sleep(1);
		a_p = mx_to_pxcoord(mx_mult(rotation, pxcoord_to_mx(a_p)));
		b_p = mx_to_pxcoord(mx_mult(rotation, pxcoord_to_mx(b_p)));
		c_p = mx_to_pxcoord(mx_mult(rotation, pxcoord_to_mx(c_p)));
		d_p = mx_to_pxcoord(mx_mult(rotation, pxcoord_to_mx(d_p)));
		fill_image_with_color(&vars.img_vars, BLACK);
		draw_line(&vars.img_vars, xwin_coord(a_p), xwin_coord(b_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b_p), xwin_coord(c_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c_p), xwin_coord(d_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d_p), xwin_coord(a_p), WHITE);
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	}


	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);


	mlx_loop(vars.mlx_ptr);
}