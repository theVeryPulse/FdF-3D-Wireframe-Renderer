// #include "fdf.h"

// void	draw_colored_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b)
// {
// 	bool		slope_greater_than_1;
// 	bool		slope_is_negative;
// 	int			delta_y;
// 	int			delta_x;
// 	int			error;
// 	t_px_coord	point;
// 	double		t;
// 	double		dt;
// 	t_argb		color;

// 	if (a.x > b.x)
// 	{
// 		px_coord_swap(&a, &b);
// 	}
// 	delta_x = ft_abs(b.x - a.x);
// 	delta_y = ft_abs(b.y - a.y);
// 	/* if (delta_x == delta_y)
// 	{
// 		return (draw_colored_diagonal_line(img_vars, a, b));
// 	}
// 	if (delta_x == 0 || delta_y == 0)
// 	{
// 		return (draw_colored_grid_line(img_vars, a, b));
// 	} */
// 	/* Slope < 0 */
// 	if ((a.x < b.x) && (a.y > b.y))
// 	{
// 		a.y = -a.y;
// 		b.y = -b.y;
// 		slope_is_negative = true;
// 	}
// 	else
// 	{
// 		slope_is_negative = false;
// 	}

// 	/* Slope > 1 */
// 	if (delta_y > delta_x)
// 	{
// 		int_swap(&a.x, &a.y);
// 		int_swap(&b.x, &b.y);
// 		slope_greater_than_1 = true;
// 	}
// 	else
// 	{
// 		slope_greater_than_1 = false;
// 	}
// 	if (a.x > b.x)
// 	{
// 		px_coord_swap(&a, &b);
// 	}
// 	delta_x = ft_abs(b.x - a.x);
// 	delta_y = ft_abs(b.y - a.y);
// 	error = 2 * delta_y - delta_x;
// 	point = a;
// 	t = 0.0;
// 	dt = 1.0 / ft_abs(b.x - a.x);
// 	while (point.x <= b.x)
// 	{
// 		color = gradient_color(t, a.color, b.color);
// 		if (slope_greater_than_1 && slope_is_negative)
// 		{
// 			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = -point.x}, color);
// 			// printf("(%d,%d)\n", point.y, -point.x);
// 		}
// 		else if (slope_is_negative)
// 		{
// 			// printf("(%d,%d)\n", point.x, -point.y);
			
// 			put_pixel_img(img_vars, (t_px_coord){.x = point.x, .y = -point.y}, color);
// 		}
// 		else if (slope_greater_than_1)
// 		{
// 			// printf("(%d,%d)\n", point.y, point.x);
// 			put_pixel_img(img_vars, (t_px_coord){.x = point.y, .y = point.x}, color);
// 		}
// 		else
// 		{
// 			// printf("(%d,%d)\n", point.x, point.y);
// 			put_pixel_img(img_vars, point, color);
// 		}
// 		if (error > 0)
// 		{
// 			point.y++;
// 			error += 2 * (delta_y - delta_x);
// 		}
// 		else
// 		{
// 			error += 2 * delta_y;
// 		}
// 		point.x++;
// 		t += dt;
// 	}
// }

// void	draw_diagonal_line(t_img_vars *image, t_px_coord a, t_px_coord b,
// 							int color)
// {
// 	t_px_coord	point;
// 	int		xstep;
// 	int		ystep;
	
// 	if (!image || ft_abs(b.x - a.x) != ft_abs(b.y - a.y))
// 		return ;
// 	if (a.x > b.x)
// 	{
// 		px_coord_swap(&a, &b);
// 	}
// 	point = a;
// 	ystep = 1 + (b.y < a.y) * (-2);
// 	while (point.x <= b.x)
// 	{
// 		put_pixel_img(image, point, color);
// 		point.x++;
// 		point.y += ystep;
// 	}
// }

// void	draw_grid_line(t_img_vars *img_vars, t_px_coord a, t_px_coord b,
// 						int color)
// {
// 	t_px_coord	point;

// 	if (b.x == a.x)
// 	{
// 		if (a.y > b.y)
// 			int_swap(&a.y, &b.y);
// 		point = a;
// 		while (point.y++ <= b.y)
// 		{
// 			put_pixel_img(img_vars, point, color);
// 		}
// 		return ;
// 	}
// 	if (b.y == a.y)
// 	{
// 		if (a.x > b.x)
// 			int_swap(&a.x, &b.x);
// 		point = a;
// 		while (point.x++ <= b.x)
// 		{
// 			put_pixel_img(img_vars, point, color);
// 		}
// 		return ;
// 	}
// }
