/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:30:56 by Philip            #+#    #+#             */
/*   Updated: 2024/02/04 22:30:41 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// Put pixel onto the image.
void	put_pixel_img(t_img_vars *img_vars, t_px_coord coord, t_color color)
{
	unsigned char	*dst;
	ptrdiff_t		offset;

	if (coord.x >= WIDTH || coord.x < 0 || coord.y >= HEIGHT || coord.y < 0)
		return ;
	offset = coord.y * img_vars->line_size + coord.x * (img_vars->bits_per_pixel / 8);
	dst = img_vars->addr + offset;
	*(unsigned int *)dst = color;
}

void	fill_image_with_color(t_img_vars *img_vars, int color)
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
			put_pixel_img(img_vars, point, color);
			point.y++;
		}
		point.x++;
	}
}

void	draw_diagonal_line(t_img_vars *image, t_px_coord start, t_px_coord end, int color)
{
	t_px_coord	point;
	int		xstep;
	int		ystep;
	
	if (!image || ft_abs(end.x - start.x) != ft_abs(end.y - start.y))
		return ;
	if (start.x > end.x)
	{
		swap(&start.x, &end.x);
		swap(&start.y, &end.y);
	}
	point = start;
	ystep = 1 + (end.y < start.y) * (-2);
	while (point.x <= end.x)
	{
		put_pixel_img(image, point, color);
		point.x++;
		point.y += ystep;
	}
}
void	draw_grid_line(t_img_vars *img_vars, t_px_coord start, t_px_coord end, int color)
{
	t_px_coord	point;

	if (end.x == start.x)
	{
		if (start.y > end.y)
			swap(&start.y, &end.y);
		point = start;
		while (point.y++ <= end.y)
		{
			put_pixel_img(img_vars, point, color);
		}
		return ;
	}
	if (end.y == start.y)
	{
		if (start.x > end.x)
			swap(&start.x, &end.x);
		point = start;
		while (point.x++ <= end.x)
		{
			put_pixel_img(img_vars, point, color);
		}
		return ;
	}
}

void	draw_line(t_img_vars *img_vars, t_px_coord start, t_px_coord end, int color)
{
	bool		slope_greater_than_1;
	bool		slope_is_negative;
	int			delta_y;
	int			delta_x;
	int			error;
	t_px_coord	point;

	
	if (start.x > end.x)
	{
		swap(&start.x, &end.x);
		swap(&start.y, &end.y);
	}
	delta_x = ft_abs(end.x - start.x);
	delta_y = ft_abs(end.y - start.y);
	if (delta_x == delta_y)
	{
		draw_diagonal_line(img_vars, start, end, color);
		return ;
	}
	if (delta_x == 0 || delta_y == 0)
	{
		draw_grid_line(img_vars, start, end, color);
		return ;
	}
	/* Slope < 0 */
	if ((start.x < end.x) && (start.y > end.y))
	{
		start.y = -start.y;
		end.y = -end.y;
		slope_is_negative = true;
	}
	else
	{
		slope_is_negative = false;
	}

	/* Slope > 1 */
	if (delta_y > delta_x)
	{
		swap(&start.x, &start.y);
		swap(&end.x, &end.y);
		slope_greater_than_1 = true;
	}
	else
	{
		slope_greater_than_1 = false;
	}
	if (start.x > end.x)
	{
		swap(&start.x, &end.x);
		swap(&start.y, &end.y);
	}
	delta_x = ft_abs(end.x - start.x);
	delta_y = ft_abs(end.y - start.y);
	error = 2 * delta_y - delta_x;
	point = start;
	while (point.x <= end.x)
	{
		if (slope_greater_than_1 && slope_is_negative)
		{
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x}, WHITE);
			// printf("(%d,%d)\n", point.y, -point.x);
		}
		else if (slope_is_negative)
		{
			// printf("(%d,%d)\n", point.x, -point.y);
			put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y}, WHITE);
		}
		else if (slope_greater_than_1)
		{
			// printf("(%d,%d)\n", point.y, point.x);
			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x}, WHITE);
		}
		else
		{
			// printf("(%d,%d)\n", point.x, point.y);
			put_pixel_img(img_vars, point, WHITE);
		}
		if (error > 0)
		{
			point.y++;
			error += 2 * (delta_y - delta_x);
		}
		else
		{
			error += 2 * delta_y;
		}
		point.x++;
	}
}
