/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:35 by Philip            #+#    #+#             */
/*   Updated: 2024/02/21 17:57:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	round_double(double n)
{
	if (n > 0)
		return ((int)(n + 0.5));
	else
		return ((int)(n - 0.5));
}

t_mx	mx_mult(int mx_count, ...)
{
	va_list	ap;
	t_mx	product;
	t_mx	next_mx;

	if (mx_count < 1)
		return ((t_mx){0});
	va_start(ap, mx_count);
	product = va_arg(ap, t_mx);
	while (mx_count > 1)
	{
		next_mx = va_arg(ap, t_mx);
		product = mxa_mult_mxb(product, next_mx);
		mx_count--;
	}
	va_end(ap);
	return (product);
}

t_mx	mxa_mult_mxb(t_mx mxa, t_mx mxb)
{
	t_mx	product;
	int		i;
	float	entry;
	int		p_row_i;
	int		p_col_i;

	if (mxa.col_num != mxb.row_num)
	{
		ft_putstr_fd(KRED, STDERR_FILENO);
		ft_putstr_fd("WARNING:", STDERR_FILENO);
		ft_putstr_fd(KWHT, STDERR_FILENO);
		ft_putendl_fd("Incorrect number of coloumns and rows for matrix "
			"multiplication", STDERR_FILENO);
		return ((t_mx){0});
	}
	product = (t_mx){.row_num = mxa.row_num, .col_num = mxb.col_num};
	p_row_i = 0;
	while (p_row_i < product.row_num)
	{
		p_col_i = 0;
		while (p_col_i <product.col_num)
		{
			entry = 0;
			i = 0;
			while (i < mxa.col_num)
			{
				entry += mxa.entries[p_row_i][i] * mxb.entries[i][p_col_i];
				i++;
			}
			product.entries[p_row_i][p_col_i] = entry;
			p_col_i++;
		}
		p_row_i++;
	}
	return (product);
}

/**
 * @brief Returns the pixel coordinates in raster space based on the screen
 * space coordinates.
 * 
 * @param p_point 
 * @return (t_px_coord) The coordinate of the pixel in raster space
 */
t_px_coord	old_raster_coord(t_px_coord p_point)
{
	t_px_coord	result;

	result.x = p_point.x + WIDTH / 2;
	result.y = -p_point.y + HEIGHT / 2;
	// ft_printf("P-system: (%d,%d), X-system: (%d,%d)\n", p_point.x, p_point.y, result.x, result.y);
	return (result);
}

t_px_coord	raster_coord(t_mx screen_coord)
{
	t_px_coord	raster_coord;

	raster_coord = mx_to_pxcoord(screen_coord);
	raster_coord.x = raster_coord.x + WIDTH / 2;
	raster_coord.y = -raster_coord.y + HEIGHT / 2;
	// ft_printf("P-system: (%d,%d), X-system: (%d,%d)\n", p_point.x, p_point.y, result.x, result.y);
	return (raster_coord);
}

t_mx	pxcoord_to_mx(t_px_coord px_coord)
{
	t_mx	mx;

	mx.col_num = 1;
	mx.row_num = 2;
	mx.entries[0][0] = (double)(px_coord.x);
	mx.entries[1][0] = (double)(px_coord.y);
	return (mx);
}

t_px_coord	mx_to_pxcoord(t_mx mx)
{
	t_px_coord	px_coord;

	/* if (mx.col_num != 1 || mx.row_num != 2)
	{
		ft_putstr_fd(KRED, STDERR_FILENO);
		ft_putendl_fd("WARNING: Matrix cannot be transformed into pixel coordinates", STDERR_FILENO);
		ft_putstr_fd(KWHT, STDERR_FILENO);
		return ((t_px_coord){0});
	} */
	px_coord.x = round_double(mx.entries[0][0]);
	px_coord.y = round_double(mx.entries[1][0]);
	return (px_coord);
}

// Returns a 3x3 matrix that rotates a vector by 'angle' degrees, 'angle must be
// in radians
t_mx	rot_x_mx(double angle)
{
	t_mx	rot_x;

	rot_x = (t_mx){.row_num = 3, .col_num = 3,
		.entries = {
			{1, 0, 0},
			{0, cos(angle), -sin(angle)},
			{0, sin(angle), cos(angle)},
		}
	};
	return (rot_x);
}

// Returns a 3x3 matrix that rotates a vector by 'angle' degrees, 'angle must be
// in radians
t_mx	rot_y_mx(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){.row_num = 3, .col_num = 3,
		.entries = {
			{cos(angle), 0, sin(angle)},
			{0, 1, 0},
			{-sin(angle), 0, cos(angle)},
		}
	};
	return (rot_y);
}

// Returns a 3x3 matrix that rotates a vector by 'angle' degrees, 'angle must be
// in radians
t_mx	rot_z_mx(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){.row_num = 3, .col_num = 3,
		.entries = {
			{cos(angle), -sin(angle), 0},
			{sin(angle), cos(angle), 0},
			{0, 0, 1}
		}
	};
	return (rot_z);
}

t_mx	psp_proj_mx(t_mx coord)
{
	t_mx	proj_mx;
	double	x_co;
	double	y_co;
	double	distance;

	distance = 500;
	x_co = fabs(coord.entries[0][0]) / (distance - coord.entries[2][0]);
	y_co = fabs(coord.entries[1][0]) / (distance - coord.entries[2][0]);
	printf("x_co: %f, y_co: %f\n", x_co, y_co);
	proj_mx = (t_mx){.row_num = 2, .col_num = 4,
		.entries = {
			{x_co, 0, 0},
			{0, y_co, 0}
		}
	};
	return (proj_mx);
}

t_mx	isometric_proj(void)
{
	t_mx	iso_proj;

	iso_proj = mx_mult(2, rot_x_mx_4x4(35.264 * PI/ 180), rot_y_mx_4x4(45 * PI / 180));
	return (iso_proj);
}

t_mx	rot_x_mx_4x4(double angle)
{
	t_mx	rot_x;

	rot_x = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {
			{1, 0, 0, 0},
			{0, cos(angle), -sin(angle), 0},
			{0, sin(angle), cos(angle), 0},
			{0, 0, 0, 1}
		}
	};
	return (rot_x);
}

t_mx	rot_y_mx_4x4(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {
			{cos(angle), 0, sin(angle), 0},
			{0, 1, 0, 0},
			{-sin(angle), 0, cos(angle), 0},
			{0, 0, 0, 1}
		}
	};
	return (rot_y);
}

t_mx	rot_z_mx_4x4(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {
			{cos(angle), -sin(angle), 0, 0},
			{sin(angle), cos(angle), 0, 0},
			{0, 0, 1, 0},
			{0, 0, 0, 1}
		}
	};
	return (rot_z);
}
