/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handlers.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 01:20:59 by Philip            #+#    #+#             */
/*   Updated: 2024/04/09 01:30:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HANDLERS_H
# define EVENT_HANDLERS_H

# include "../fdf.h"

int		handle_key_caval(int key, t_vars *vars);
int		destroy_exit(t_vars *vars);
int		handle_key_isometric(int key, t_vars *vars);
int		mouse_button(int button, int x, int y, void *p);
int		mouse_motion(int x, int y, void *p);

#endif
