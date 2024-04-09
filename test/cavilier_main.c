/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cavilier_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:59:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char const *argv[])
{
	t_vars	vars;
	char	*content;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]); 
	printf("Content as one string:\n%s", content);
	map_check(content);
	
	printf("Map checked\n");
	vars.map = map_build(content);
	print_map(&vars.map);
	free(content);
	printf("Total columns: %d, total rows: %d\n", vars.map.col_num, vars.map.row_num);

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");

	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

	// Initialize vertexes' real coordinates
	int	col;
	int	row;
	int	i;
	double	init_scale;

	init_scale = 50.0;
	row = 0;
	i = 0;
	while (row < vars.map.row_num)
	{
		col = 0;
		while (col < vars.map.col_num)
		{
			vars.map.vertexes[col + row * vars.map.col_num].real_coord = point_real_coord(
				init_scale * col,
				init_scale * vars.map.vertexes[col + row * vars.map.col_num].height,
				-init_scale * (vars.map.row_num - row - 1));
			col++;
		}
		row++;
	}

	render_colored_caval_model(&vars);

	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

	mlx_key_hook(vars.win_ptr, handle_key_isometric, &vars);
	mlx_hook(vars.win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_button, &vars);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);

	mlx_loop(vars.mlx_ptr);
}
