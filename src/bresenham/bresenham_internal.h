/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_internal.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:52:33 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:53:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_INTERNAL_H
# define BRESENHAM_INTERNAL_H

# include "bresenham.h"

void
bresenham_normalize_coords(
	t_px_coord *a, t_px_coord *b, t_slope_property *slope);

void
bresenham_draw_colored_pixels(
	t_img_vars *img_vars, t_px_coord a, t_px_coord b, t_slope_property slope);

#endif
