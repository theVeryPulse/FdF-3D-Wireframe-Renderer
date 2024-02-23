/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:35 by Philip            #+#    #+#             */
/*   Updated: 2024/02/22 19:16:05 by Philip           ###   ########.fr       */
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
	return (result);
}

t_px_coord	raster_coord(t_mx screen_coord)
{
	t_px_coord	raster_coord;

	raster_coord = mx_to_pxcoord(screen_coord);
	raster_coord.x = raster_coord.x + WIDTH / 2;
	raster_coord.y = -raster_coord.y + HEIGHT / 2;
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
		.entries = {{1, 0, 0},
					{0, cos(angle), -sin(angle)},
					{0, sin(angle), cos(angle)}}};
	return (rot_x);
}

// Returns a 3x3 matrix that rotates a vector by 'angle' degrees, 'angle must be
// in radians
t_mx	rot_y_mx(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){.row_num = 3, .col_num = 3,
		.entries = {{cos(angle), 0, sin(angle)},
					{0, 1, 0},
					{-sin(angle), 0, cos(angle)}}};
	return (rot_y);
}

// Returns a 3x3 matrix that rotates a vector by 'angle' degrees, 'angle must be
// in radians
t_mx	rot_z_mx(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){.row_num = 3, .col_num = 3,
		.entries = {{cos(angle), -sin(angle), 0},
					{sin(angle), cos(angle), 0},
					{0, 0, 1}}};
	return (rot_z);
}

t_mx	rot_x_mx_4x4(double angle)
{
	t_mx	rot_x;

	rot_x = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {{1, 0, 0, 0},
					{0, cos(angle), -sin(angle), 0},
					{0, sin(angle), cos(angle), 0},
					{0, 0, 0, 1}}};
	return (rot_x);
}

t_mx	rot_y_mx_4x4(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {{cos(angle), 0, sin(angle), 0},
					{0, 1, 0, 0},
					{-sin(angle), 0, cos(angle), 0},
					{0, 0, 0, 1}}};
	return (rot_y);
}

t_mx	rot_z_mx_4x4(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){.row_num = 4, .col_num = 4,
		.entries = {{cos(angle), -sin(angle), 0, 0},
					{sin(angle), cos(angle), 0, 0},
					{0, 0, 1, 0},
					{0, 0, 0, 1}}};
	return (rot_z);
}
