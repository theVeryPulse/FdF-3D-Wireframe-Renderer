/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_vars.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 19:29:53 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 19:30:08 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_VARS_H
# define IMG_VARS_H

typedef struct s_img_vars
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}	t_img_vars;

#endif