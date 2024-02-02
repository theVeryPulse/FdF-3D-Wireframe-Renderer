/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:06:48 by Philip            #+#    #+#             */
/*   Updated: 2024/02/02 21:42:37 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	change_screen_color(t_vars *vars, int color)
{
	if (!vars)
		return ;
	fill_image_with_color(&vars->img_vars, color);
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr, vars->img_vars.img_ptr, 0, 0);
}

int	destroy_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	exit (0);
}

int	handle_key(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
	{
		destroy_exit(vars);
	}
	else if (key == XK_r)
	{
		change_screen_color(vars, create_argb(200, 0, 0, 1));
	}
	else if (key == XK_b)
	{
		change_screen_color(vars, create_argb(0, 0, 0, 0));
	}
}

void	mouse_button(int button,int x,int y, void *p)
{
	printf("Mouse in Win, button %d at %dx%d.\n", button, x, y);
}

int	mouse_motion(int x,int y, void *p)
{
	printf("Mouse moving in Win, at %dx%d.\n",x,y);
}

int	main(int argc, char **argv)
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
