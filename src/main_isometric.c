/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_isometric.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:48 by Philip            #+#    #+#             */
/*   Updated: 2024/02/23 18:51:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_up_hooks_isometric(t_vars *vars)
{
	mlx_key_hook(vars->win_ptr, isometric_handle_key, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit, vars);
	mlx_mouse_hook(vars->win_ptr, mouse_button, vars);
	mlx_hook(vars->win_ptr, MotionNotify, PointerMotionMask, mouse_motion, NULL);
}

int	main(int argc, char const *argv[])
{
	t_vars	vars;
	char	*content;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]); 
	map_check(content);
	vars.map = build_map(content);
	free(content);
	populate_vertexes_in_map(&vars);
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "fdf");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);
	transform_all_vertexes(vars.map.vertexes,
							vars.map.row_num * vars.map.col_num,
							isometric4x4());
	render_colored_ortho_model(&vars);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	set_up_hooks_isometric(&vars);
	mlx_loop(vars.mlx_ptr);
}
