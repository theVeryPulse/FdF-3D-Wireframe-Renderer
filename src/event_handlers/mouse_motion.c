/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_motion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:13:01 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:13:12 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Handles mouse motion events.
 * 
 * @param x The x-coordinate of the mouse cursor.
 * @param y The y-coordinate of the mouse cursor.
 * @param p A pointer to additional data (not used in this function).
 * @note Does not return any value, function prototype to match MiniLibX:
 *       mlx_mouse_hook(t_win_list *win,int (*funct)(),void *param)
 */
int	mouse_motion(int x, int y, void *p)
{
	ft_printf("Mouse moving in Win, at %dx%d.\n", x, y);
}