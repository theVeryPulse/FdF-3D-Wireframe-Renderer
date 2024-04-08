/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:23:33 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:24:30 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "img_vars.h"
# include "px_coord.h"

void	image_put_pixel(t_img_vars *img_vars, t_px_coord coord, t_argb color);
void	image_fill_color(t_img_vars *img_vars, int color);

#endif