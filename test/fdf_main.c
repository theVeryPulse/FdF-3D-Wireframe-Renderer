/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:52:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:20:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_map *map)
{
	for (size_t i = 0; i < map->row_num; i++)
	{
		for (size_t j = 0; j < map->col_num; j++)
		{
			printf("%x ", map->vertexes[map->col_num * i + j].color);
		}
		printf("\n");
	}
}

t_mx	point_real_coord(double x, double y, double z)
{
	t_mx	point;

	point = (t_mx){.row_num = 4, .col_num = 1, .entries = {{x}, {y}, {z}, {1}}};
	return (point);
}

t_mx	isometric4x4(void)
{
	t_mx	iso_proj;

	// iso_proj = mx_mult(2, rot_x_mx_4x4(45 * PI/ 180), rot_y_mx_4x4(-10 * PI / 180));
	iso_proj = mxa_mult_mxb(rot_x_mx_4x4(35.264 * PI/ 180),
							rot_y_mx_4x4(-45 * PI / 180));
	return (iso_proj);
}

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
			vars.map.vertexes[col + row * vars.map.col_num].real_coord = mx_mult(2, 
				isometric4x4(),
				vars.map.vertexes[col + row * vars.map.col_num].real_coord);
			col++;
		}
		row++;
	}

	// render_ortho_model(&vars);
	render_colored_ortho_model(&vars);



	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

	mlx_key_hook(vars.win_ptr, handle_key, &vars);
	mlx_hook(vars.win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_button, &vars);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);

	mlx_loop(vars.mlx_ptr);
}
