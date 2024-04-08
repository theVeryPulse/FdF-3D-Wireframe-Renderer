/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cavalier.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:39:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:41:21 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "map.h"
#include "scree_size.h"

static void	set_up_hooks_caval(t_vars *vars);

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
	// map_populate_vertexes(&vars.map);
	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "fdf cavalier");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
			&vars.img_vars.bits_per_pixel,
			&vars.img_vars.line_size,
			&vars.img_vars.endian);
	render_colored_caval_model(&vars);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr,
		0, 0);
	set_up_hooks_caval(&vars);
	mlx_loop(vars.mlx_ptr);
}

static void	set_up_hooks_caval(t_vars *vars)
{
	press_key_hook(vars->win_ptr, caval_handle_key, vars);
	mlx_hook(vars->win_ptr, DestroyNotify, ButtonReleaseMask,
		destroy_exit, vars);
	mlx_mouse_hook(vars->win_ptr, mouse_button, vars);
	mlx_hook(vars->win_ptr, MotionNotify, PointerMotionMask, mouse_motion,
		NULL);
}
