/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:52:53 by Philip            #+#    #+#             */
/*   Updated: 2024/02/16 16:04:45 by Philip           ###   ########.fr       */
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
	
	


	mlx_key_hook(vars.win_ptr, handle_key, &vars);
	mlx_hook(vars.win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, &vars);
	mlx_mouse_hook(vars.win_ptr, mouse_button, &vars);
	mlx_hook(vars.win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);

	mlx_loop(vars.mlx_ptr);
}
