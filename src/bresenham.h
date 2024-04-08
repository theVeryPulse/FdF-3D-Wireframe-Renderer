/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:34:55 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:33:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRESENHAM_H
# define BRESENHAM_H

# include "img_vars.h"
# include "px_coord.h"
# include <stdbool.h>

typedef struct s_delta
{
	int	x;
	int	y;
}	t_delta;

typedef struct s_slope_property
{
	bool	is_greater_than_1;
	bool	is_negative;
}	t_slope_property;

typedef struct s_transition
{
	double	curr;
	double	step;
}	t_transition;

void	bresenham_draw_colored_line(
		t_img_vars *img_vars, t_px_coord a, t_px_coord b);

#endif