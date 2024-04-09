/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moust_button.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:12:47 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:13:24 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Handles mouse button events.
 *
 * @param button The button code of the pressed mouse button.
 * @param x The x-coordinate of the mouse cursor in X window.
 * @param y The y-coordinate of the mouse cursor in X window.
 * @param p A pointer to additional data (not used in this function).
 * @note Does not return any value, function prototype to match MiniLibX:
 *       mlx_mouse_hook(t_win_list *win,int (*funct)(),void *param)
 */
int	mouse_button(int button, int x, int y, void *p)
{
	ft_printf("Mouse in Win, button %d at %dx%d.\n", button, x, y);
}