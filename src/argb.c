/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:46 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 17:46:01 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "argb.h"

/**
 * @brief Create a int value representing arpg
 * 
 * @param alpha Transparency
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return int (0xAARRGGBB)
 */
t_argb	argb(unsigned char alpha, unsigned char r, unsigned char g,
				unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, alpha});
}

/**
 * @brief Retrieves the alpha component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The alpha component of the color.
 */
unsigned char	get_a(t_argb argb)
{
	return (((unsigned char *)&argb)[3]);
}

/**
 * @brief Retrieves the red component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The red component of the color.
 */
unsigned char	get_r(t_argb argb)
{
	return (((unsigned char *)&argb)[2]);
}

/**
 * @brief Retrieves the green component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The green component of the color.
 */
unsigned char	get_g(t_argb argb)
{
	return (((unsigned char *)&argb)[1]);
}

/**
 * @brief Retrieves the blue component from a 32-bit ARGB color value.
 *
 * @param argb The 32-bit ARGB color value.
 * @return The blue component of the color.
 */
unsigned char	get_b(t_argb argb)
{
	return (((unsigned char *)&argb)[0]);
}
