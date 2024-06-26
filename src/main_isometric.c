/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_isometric.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:48 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:24:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "read_file.h"
#include "screen_size.h"
#include "event_handlers/event_handlers.h"
#include "transformation_matrix/transformation_matrix.h"

static void	set_up_hooks_isometric(t_vars *vars);

/**
 * Only creates one X image, to update the window, the image is repainted and
 * then put to the X window.
 */
int	main(int argc, char const *argv[])
{
	t_vars	vars;
	char	*content;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]);
	map_check(content);
	map_build(&vars.map, content);
	free(content);
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
	put_image_to_window_vars(&vars);
	set_up_hooks_isometric(&vars);
	mlx_loop(vars.mlx_ptr);
}

static void	set_up_hooks_isometric(t_vars *vars)
{
	press_key_hook(vars->win_ptr, handle_key_isometric, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask, destroy_exit,
		vars);
	mlx_mouse_hook(vars->win_ptr, mouse_button, vars);
	mlx_hook(vars->win_ptr, MotionNotify, PointerMotionMask, mouse_motion,
		NULL);
}
