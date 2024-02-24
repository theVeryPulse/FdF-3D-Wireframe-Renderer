/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:33:08 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:49:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	isometric_handle_key(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
	else if (key == XK_Left || key == XK_Right || key == XK_Up
		|| key == XK_Down)
		translate(vars, key);
	else if (key == XK_i || key == XK_o)
		scale(vars, key);
	else if (key == XK_q || key == XK_e || key == XK_w || key == XK_s
		|| key == XK_a || key == XK_d)
		rotate(vars, key);
}

void	caval_handle_key(int key, t_vars *vars)
{
	ft_printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
	else if (key == XK_Left || key == XK_Right || key == XK_Up
		|| key == XK_Down)
		translate_caval(vars, key);
	else if (key == XK_i || key == XK_o)
		scale_caval(vars, key);
}

void	mouse_button(int button, int x, int y, void *p)
{
	ft_printf("Mouse in Win, button %d at %dx%d.\n", button, x, y);
}

int	mouse_motion(int x, int y, void *p)
{
	ft_printf("Mouse moving in Win, at %dx%d.\n", x, y);
}

int	destroy_exit(t_vars *vars)
{
	mlx_destroy_image(vars->mlx_ptr, vars->img_vars.img_ptr);
	mlx_destroy_window(vars->mlx_ptr, vars->win_ptr);
	mlx_destroy_display(vars->mlx_ptr);
	free(vars->mlx_ptr);
	free(vars->map.vertexes);
	exit (0);
}
