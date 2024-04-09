/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_cavalier.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:05:36 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:30:25 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handlers.h"
#include "transform.h"
#include "../fdf.h"
#include "libft.h"

/**
 * @brief Handles key events for the cavalier view mode.
 *
 * @param key The key code of the pressed key.
 * @param vars Pointer to the variables structure.
 * @note Does not return any value, function prototype to match MiniLibX:
 *       mlx_key_hook(t_win_list *win,int (*funct)(),void *param)
 */
int	handle_key_caval(int key, t_vars *vars)
{
	ft_printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
	else if (key == XK_Left || key == XK_Right
		|| key == XK_Up || key == XK_Down
		|| key == XK_i || key == XK_o)
		transform(vars, key);
}
