/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   px_coord.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:43:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:46:17 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PX_COORD_H
# define PX_COORD_H

# include "argb.h"

typedef struct s_px_coord
{
	int		x;
	int		y;
	t_argb	color;
}	t_px_coord;

#endif