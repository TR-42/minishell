/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_append_ptr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:21:19 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 11:37:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem/ft_mem.h"
#include "ft_vect/ft_vect.h"

#include "_filectrl_tools.h"

__attribute__((nonnull))
bool	vect_append_ptr(t_vect *vect, const void *elem)
{
	unsigned char	*p;
	size_t			index;

	index = vect->len;
	if (vect->p == NULL || vect->elemsize == 0)
		return (false);
	if (vect->cap == 0 || (vect->cap - 1) <= index
		&& !vect_reserve(vect, index + FT_VECT_EXPAND_STEP))
		return (false);
	p = vect->p;
	ft_memmove(p + (index * vect->elemsize), &elem, vect->elemsize);
	vect->len += 1;
	ft_bzero(p + (vect->len * vect->elemsize), vect->elemsize);
	return (true);
}
