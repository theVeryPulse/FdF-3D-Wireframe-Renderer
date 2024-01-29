/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 12:42:46 by Philip            #+#    #+#             */
/*   Updated: 2024/01/29 22:31:35 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Create a int value representing trpg
 * 
 * @param alpha Transparency
 * @param r Red
 * @param g Green
 * @param b Blue
 * @return int 
 */
int	create_trgb(unsigned char alpha, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, alpha});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}



