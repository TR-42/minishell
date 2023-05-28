/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_insert_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:24:11 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 18:29:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

#include "ft_math/ft_math.h"
#include "ft_mem/ft_mem.h"
#include "ft_vect/ft_vect.h"

#include "_build_cmd.h"

// !! MUST_PRINT_ERROR_IN_CALLER
__attribute__((nonnull(1)))
bool	vect_insert_range(t_vect *vect, size_t index, void *d, size_t len)
{
	void	*dst;
	size_t	datasize;

	if (!can_addp(vect->len, len))
		return (false);
	if (vect->cap < vect->len + len && !vect_reserve(vect, vect->len + len))
		return (false);
	dst = vect->p + (index * vect->elemsize);
	datasize = len * vect->elemsize;
	ft_memmove(dst + datasize, dst, (vect->len - index) * vect->elemsize);
	if (d != NULL)
		ft_memmove(dst, d, datasize);
	vect->len += len;
	return (true);
}
