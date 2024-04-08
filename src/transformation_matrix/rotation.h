/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:54:56 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:55:39 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "../matrix.h"

t_mx	x_rotation4x4(double angle);
t_mx	y_rotation4x4(double angle);
t_mx	z_rotation4x4(double angle);

#endif