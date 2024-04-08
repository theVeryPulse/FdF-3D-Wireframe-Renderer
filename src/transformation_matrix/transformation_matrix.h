/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation_matrix.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 23:56:52 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 23:58:46 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_MATRIX_H
# define TRANSFORMATION_MATRIX_H

# include "../matrix.h"

t_mx	translation4x4_for_key(int key);
t_mx	scale4x4_for_key(int key);
t_mx	scale4x4_for_key(int key);
t_mx	isometric4x4(void);

#endif
