/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_conversion.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:08:05 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 00:39:26 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COORD_CONVERSION_H
# define COORD_CONVERSION_H

# include "../matrix.h"
# include "../px_coord.h"

t_mx		screen_coord_ortho(t_mx world_coord);
t_mx		screen_coord_caval(t_mx world_coord);
t_px_coord	raster_coord(t_mx screen_coord);

#endif
