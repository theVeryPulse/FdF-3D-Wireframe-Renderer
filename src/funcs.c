/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:53:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/03 22:53:16 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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