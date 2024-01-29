/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 17:20:53 by Philip            #+#    #+#             */
/*   Updated: 2024/01/29 22:50:06 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "mlx.h"
# include "mlx_int.h"
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <X11/keysym.h>
# include <X11/X.h>

int	create_trgb(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b);

#endif