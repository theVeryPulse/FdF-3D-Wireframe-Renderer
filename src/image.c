/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:30:56 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:23:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
// #include "img_vars.h"
#include "scree_size.h"
// #include "px_coord.h"
#include <stddef.h>

/**
 * @brief Puts a pixel with the specified color at the given coordinates on the 
 *        mlx image.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param coord The coordinates of the pixel.
 * @param color The color of the pixel.
 */
void	image_put_pixel(t_img_vars *img_vars, t_px_coord coord, t_argb color)
{
	unsigned char	*dst;
	ptrdiff_t		offset;

	if (coord.x >= WIDTH || coord.x < 0 || coord.y >= HEIGHT || coord.y < 0)
		return ;
	offset = coord.y * img_vars->line_size
		+ coord.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = color;
}

/**
 * @brief Fills the entire mlx image with the specified color.
 *
 * @param img_vars Pointer to the image variables structure.
 * @param color The color to fill the image with.
 */
void	image_fill_color(t_img_vars *img_vars, int color)
{
	t_px_coord	point;

	if (!img_vars)
		return ;
	point = (t_px_coord){0};
	while (point.x < WIDTH)
	{
		point.y = 0;
		while (point.y < HEIGHT)
		{
			image_put_pixel(img_vars, point, color);
			point.y++;
		}
		point.x++;
	}
}

/**
 * @brief Changes the color of entire X window to the specified color.
 *
 * @param vars Pointer to the variables structure.
 * @param color The color to change the screen to.
 */
void	change_screen_color(t_vars *vars, int color)
{
	if (!vars)
		return ;
	image_fill_color(&vars->img_vars, color);
	put_image_to_window_vars(vars);
}

/**
 * @brief Puts the image to the window.
 *
 * @param vars Pointer to the variables structure.
 */
void	put_image_to_window_vars(t_vars *vars)
{
	mlx_put_image_to_window(vars->mlx_ptr, vars->win_ptr,
		vars->img_vars.img_ptr, 0, 0);
}
