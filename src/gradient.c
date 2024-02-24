/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gradient.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 01:09:42 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 01:09:58 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_argb	gradient_color(double transition, t_argb start, t_argb end)
{
	t_argb	color;

	if (transition < 0 || transition > 1)
		return (start);
	color = argb(
			(0xff),
			((1 - transition) * get_r(start) + transition * get_r(end)),
			((1 - transition) * get_g(start) + transition * get_g(end)),
			((1 - transition) * get_b(start) + transition * get_b(end)));
	return (color);
}
