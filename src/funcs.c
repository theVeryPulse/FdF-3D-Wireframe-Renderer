/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 22:53:07 by Philip            #+#    #+#             */
/*   Updated: 2024/02/21 18:54:40 by Philip           ###   ########.fr       */
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
	free(vars->map.vertexes);
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
		change_screen_color(vars, argb(200, 0, 0, 1));
	}
	else if (key == XK_b)
	{
		change_screen_color(vars, argb(0, 0, 0, 0));
	}
	else if (key == XK_Left || key == XK_Right || key == XK_Up || key == XK_Down)
	{
		translate(vars, key);
	}
	else if (key == XK_i || key == XK_o)
	{
		scale(vars, key);
	}
	else if (key == XK_q || key== XK_e || key == XK_w || key == XK_s || key == XK_a || key == XK_d)
	{
		rotate(vars, key);
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
