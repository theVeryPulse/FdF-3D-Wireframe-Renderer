/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:09:42 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:46:29 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// /**
//  * @brief Computes a gradient color between two ARGB colors based on the
//  *        transition value.
//  *
//  * @param transition The transition value between the start and end colors
//  *                   (0 to 1).
//  * @param start The start color of the gradient.
//  * @param end The end color of the gradient.
//  * @return The gradient color.
//  * @note The transition value determines the proportion of each color in the
//  *       final gradient color. When t equals 0, returns 'start' color, when t
//  *       equals 1, returns 'end' color
//  */
// t_argb	gradient_color(double transition, t_argb start, t_argb end)
// {
// 	t_argb	color;

// 	if (transition < 0 || transition > 1)
// 		return (start);
// 	color = argb(
// 			(0xff),
// 			((1 - transition) * get_r(start) + transition * get_r(end)),
// 			((1 - transition) * get_g(start) + transition * get_g(end)),
// 			((1 - transition) * get_b(start) + transition * get_b(end)));
// 	return (color);
// }
