/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:27:14 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:30:52 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

/**
 * @brief Checks the validity of the map string.
 *
 * @param map_str The map string to be checked.
 * @note Checks if the string only has numbers, commas, letters, and spaces.
 */
void	map_check(char *map_str)
{
	size_t	i;

	if (!map_str)
		exit(1);
	i = 0;
	while (map_str[i] && (ft_isspace(map_str[i]) || ft_isalnum(map_str[i])
			|| ft_strchr("+-,", map_str[i])))
	{
		i++;
	}
	if (map_str[i] != '\0')
	{
		free(map_str);
		exit(1);
	}
}
