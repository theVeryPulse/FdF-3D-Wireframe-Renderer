/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:59:35 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:28:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Converts a hexadecimal string to an integer.
 *
 * @param str The hexadecimal string to convert.
 * @return The integer value of the hexadecimal string.
 */
int	hex_atoi(const char *str)
{
	size_t				i;
	int					n;
	char				*copy;
	static const char	*lower = "0123456789abcdef";

	copy = ft_strndup(str, 12);
	n = 0;
	i = 2;
	while (copy[i])
	{
		if (ft_isupper(copy[i]))
			copy[i] = ft_tolower(copy[i]);
		i++;
	}
	i = 2;
	while (ft_strchr(lower, copy[i]))
	{
		n *= 16;
		n += (int)(ft_strchr(lower, copy[i]) - lower);
		i++;
	}
	free(copy);
	return (n);
}
