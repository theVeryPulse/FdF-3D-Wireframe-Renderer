/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key_isometric.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 00:59:31 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:30:49 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_handlers.h"
#include "transform.h"
#include "../fdf.h"
#include "../transformation_matrix/transformation_matrix.h"

/**
 * @brief Handles key events for the isometric view mode.
 *
 * @param key The key code of the pressed key.
 * @param vars Pointer to the variables structure.
 * @note Does not return any value, function prototype to match MiniLibX:
 *       mlx_key_hook(t_win_list *win,int (*funct)(),void *param)
 */
int	handle_key_isometric(int key, t_vars *vars)
{
	printf("%d pressed\n", key);
	if (key == XK_Escape)
		destroy_exit(vars);
	else if (key == XK_Left || key == XK_Right
		|| key == XK_Up || key == XK_Down
		|| key == XK_i || key == XK_o
		|| key == XK_q || key == XK_e
		|| key == XK_w || key == XK_s
		|| key == XK_a || key == XK_d)
		transform(vars, key);
}
