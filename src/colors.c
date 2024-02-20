/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:46 by Philip            #+#    #+#             */
/*   Updated: 2024/02/20 21:51:36 by Philip           ###   ########.fr       */
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
t_argb	create_argb(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, alpha});
}

unsigned char	get_a(t_argb argb)
{
	return (((unsigned char *)&argb)[3]);
}

unsigned char	get_r(t_argb argb)
{
	return (((unsigned char *)&argb)[2]);
}

unsigned char	get_g(t_argb argb)
{
	return (((unsigned char *)&argb)[1]);
}

unsigned char	get_b(t_argb argb)
{
	return (((unsigned char *)&argb)[0]);
}



