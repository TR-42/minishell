/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:36:24 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/28 01:35:37 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"
#include "../ft_mem/ft_mem.h"

bool	vect_remove(t_vect *vect, size_t index)
{
	if (vect->len <= index)
		return (false);
	if ((index + 1) < vect->len)
		ft_memmove(vect_at(vect, index), vect_at(vect, index + 1),
			(vect->len - index + 1) * vect->elemsize);
	vect->len -= 1;
	return (true);
}
