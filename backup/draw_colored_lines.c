/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colored_lines.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 00:20:45 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:23:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// void	draw_colored_diagonal_line(t_img_vars *image, t_px_coord a,
// 		t_px_coord b)
// {
// 	t_px_coord	point;
// 	int			xstep;
// 	int			ystep;
// 	double		t;
// 	double		dt;

// 	if (!image || ft_abs(b.x - a.x) != ft_abs(b.y - a.y))
// 		return ;
// 	if (a.x > b.x)
// 		px_coord_swap(&a, &b);
// 	t = 0.0;
// 	dt = 1.0 / ft_abs(b.x - a.x);
// 	point = a;
// 	ystep = 1 + (b.y < a.y) * (-2);
// 	while (point.x <= b.x)
// 	{
// 		image_put_pixel(image, point, gradient_color(t, a.color, b.color));
// 		point.x++;
// 		point.y += ystep;
// 		t += dt;
// 	}
// }

// void	draw_colored_hori_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
// {
// 	t_px_coord	point;
// 	double		t;
// 	double		dt;
// 	t_argb		color;

// 	if (a.x != b.x)
// 		return ;
// 	if (a.x > b.x)
// 		int_swap(&a.x, &b.x);
// 	dt = 1.0 / ft_abs(b.x - a.x);
// 	point = a;
// 	while (point.x++ <= b.x)
// 	{
// 		color = gradient_color(t, a.color, b.color);
// 		image_put_pixel(img_vars, point, color);
// 		t += dt;
// 	}
// }

// void	draw_colored_verti_line(t_img_vars *img_vars, t_px_coord a,
// 		t_px_coord b)
// {
// 	t_px_coord	point;
// 	double		t;
// 	double		dt;
// 	t_argb		color;

// 	if (b.y != a.y)
// 		return ;
// 	if (a.y > b.y)
// 		int_swap(&a.y, &b.y);
// 	dt = 1.0 / ft_abs(b.y - a.y);
// 	point = a;
// 	while (point.y++ <= b.y)
// 	{
// 		color = gradient_color(t, a.color, b.color);
// 		image_put_pixel(img_vars, point, color);
// 		t += dt;
// 	}
// }

// void	draw_colored_grid_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
// {
// 	t_px_coord	point;
// 	double		t;
// 	double		dt;
// 	t_argb		color;

// 	t = 0.0;
// 	if (b.x == a.x)
// 		draw_colored_verti_line(img_vars, a, b);
// 	else if (b.y == a.y)
// 		draw_colored_hori_line(img_vars, a, b);
// }
