/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:46 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 02:33:53 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Create a int value representing trpg
 * 
 * @param alpha Transparency
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return int 
 */
t_color	create_argb(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
	return (*(int *)(unsigned char [4]){b, g, r, alpha});
}

unsigned char	get_t(int argb)
{
	return (((unsigned char *)&argb)[3]);
}

unsigned char	get_r(int argb)
{
	return (((unsigned char *)&argb)[2]);
}

unsigned char	get_g(int argb)
{
	return (((unsigned char *)&argb)[1]);
}

unsigned char	get_b(int argb)
{
	return (((unsigned char *)&argb)[0]);
}



