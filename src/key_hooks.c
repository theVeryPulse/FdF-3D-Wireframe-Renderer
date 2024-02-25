/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 22:45:03 by Philip            #+#    #+#             */
/*   Updated: 2024/02/24 22:53:20 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	press_key_hook(t_win_list *win, int (*funct)(), void *param)
{
	win->hooks[KeyPress].hook = funct;
	win->hooks[KeyPress].param = param;
	win->hooks[KeyPress].mask = KeyPressMask;
}
