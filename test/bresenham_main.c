/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:35:43 by Philip            #+#    #+#             */
/*   Updated: 2024/02/03 23:22:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char const *argv[])
{
	t_vars	vars;
	
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	// draw_line(&vars.img_vars, xwin_coord((t_px_coord){0}), xwin_coord((t_px_coord){10, 300}), WHITE);

	// Draws line in every direction
	double angle = 1 * PI / 180;
	t_matrix rotation = (t_matrix){.row_num = 2, .col_num = 2,
		.entries = {
			{cos(angle), -sin(angle)},
			{sin(angle), cos(angle)}
		}
	};
	t_px_coord	needle = (t_px_coord){.x = 0, .y = 200};
	for (int count = 0; count < 390; count++)
	{
		draw_line(&vars.img_vars, xwin_coord((t_px_coord){0}), xwin_coord(needle), WHITE);
		needle = mx_to_pxcoord(mx_mult(rotation, pxcoord_to_mx(needle)));
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	}

	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	mlx_loop(vars.mlx_ptr);
}
