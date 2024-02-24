/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:33:35 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:59:33 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mx	rot_x_mx_4x4(double angle)
{
	t_mx	rot_x;

	rot_x = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{1, 0, 0, 0},
	{0, cos(angle), -sin(angle), 0},
	{0, sin(angle), cos(angle), 0},
	{0, 0, 0, 1}}};
	return (rot_x);
}

t_mx	rot_y_mx_4x4(double angle)
{
	t_mx	rot_y;

	rot_y = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{cos(angle), 0, sin(angle), 0},
	{0, 1, 0, 0},
	{-sin(angle), 0, cos(angle), 0},
	{0, 0, 0, 1}}};
	return (rot_y);
}

t_mx	rot_z_mx_4x4(double angle)
{
	t_mx	rot_z;

	rot_z = (t_mx){
		.row_num = 4,
		.col_num = 4,
		.entries = {
	{cos(angle), -sin(angle), 0, 0},
	{sin(angle), cos(angle), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}}};
	return (rot_z);
}
