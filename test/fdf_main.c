/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:52:53 by Philip            #+#    #+#             */
/*   Updated: 2024/02/19 01:36:38 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	connect_vertexes(t_map *map)
// {
// 	int	col;
// 	int	row;

// 	row = 0;
// 	while (row < map->row_num)
// 	{
// 		col = 0;
// 		while (col < map->col_num)
// 		{
// 			if (col + 1 != map->col_num)
// 				// connect(map->vertexes[col + row * map->col_num], map->vertexes[col + 1 + row * map->col_num]);
// 			if (row + 1 != map->row_num)
// 				// connect(map->vertexes[col + row * map->col_num], map->vertexes[col + (row + 1) * map->row_num]);
// 			col++;
// 		}
// 		row++;
// 	}
// }

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
	iso_proj = mx_mult(2, rot_x_mx_4x4(35.264 * PI/ 180), rot_y_mx_4x4(-45 * PI / 180));
	return (iso_proj);
}

int main(int argc, char const *argv[])
{
	t_vars	vars;
	char	*content;
	t_map	map;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]); 
	printf("Content as one string:\n%s", content);
	map_check(content);
	
	printf("Map checked\n");
	map = build_map(content);
	print_map(&map);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

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
	while (row < map.row_num)
	{
		col = 0;
		while (col < map.col_num)
		{
			map.vertexes[col + row * map.col_num].real_coord = point_real_coord(
				init_scale * col,
				init_scale * map.vertexes[col + row * map.col_num].height,
				-init_scale * (map.row_num - row - 1)
			);
			map.vertexes[col + row * map.col_num].real_coord = mx_mult(2, 
				isometric4x4(),
				map.vertexes[col + row * map.col_num].real_coord);
			col++;
		}
		row++;
	}

	// Draw vertexes
	t_mx	ortho_proj_2x4 = (t_mx){
		.row_num = 2,
		.col_num = 4,
		.entries = {
			{1, 0, 0, 0},
			{0, 1, 0, 0}
		}
	};
	i = 0;
	while (i < map.row_num * map.col_num)
	{
		put_pixel_img(
			&vars.img_vars,
			raster_coord(mx_mult(2, ortho_proj_2x4, map.vertexes[i].real_coord)),
			map.vertexes[i].color);
		i++;
	}

	// Connect vertexes
	int	j;

	i = 0;
	while (i < map.row_num)
	{
		j = 0;
		while (j < map.col_num)
		{
			if (j != map.col_num - 1)
			{
				draw_line(&vars.img_vars,
					raster_coord(mx_mult(2, ortho_proj_2x4, map.vertexes[j + i * map.col_num].real_coord)),
					raster_coord(mx_mult(2, ortho_proj_2x4, map.vertexes[j + 1 + i * map.col_num].real_coord)),
					WHITE);
			}
			if (i != map.row_num - 1)
			{
				draw_line(&vars.img_vars,
					raster_coord(mx_mult(2, ortho_proj_2x4, map.vertexes[j + i * map.col_num].real_coord)),
					raster_coord(mx_mult(2, ortho_proj_2x4, map.vertexes[j + (i + 1) * map.col_num].real_coord)),
					WHITE);
			}
			j++;
		}
		i++;
	}






	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);

	mlx_key_hook(vars.win_ptr, handle_key, &vars);
	mlx_hook(vars.win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_button, &vars);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);

	mlx_loop(vars.mlx_ptr);
}
