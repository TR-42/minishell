/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_append_range.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:12:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/06 23:57:28 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"

#include "../ft_math/ft_math.h"
#include "../ft_mem/ft_mem.h"

static const int	g_flag_string = 1;
static const int	g_flag_not_string = 0;

static bool	vect_append_internal(
	t_vect *vect, const void *value, size_t count, int is_str)
{	
	size_t	bytes_to_copy;
	size_t	new_len;

	if (!can_mulp(vect->elemsize, count))
		return (false);
	if (!can_addp(vect->len, count))
		return (false);
	new_len = vect->len + count;
	if (vect->cap < (new_len + is_str) && !vect_reserve(vect, new_len + is_str))
		return (false);
	bytes_to_copy = vect->elemsize * count;
	ft_memmove(((unsigned char *)vect->p) + (vect->len * vect->elemsize),
		value, bytes_to_copy);
	vect->len = new_len;
	if (is_str)
		((char *)(vect->p))[vect->len] = '\0';
	return (true);
}

bool	vect_append_range(t_vect *vect, const void *value, size_t count)
{
	return (vect_append_internal(vect, value, count, g_flag_not_string));
}

bool	vect_append_str(t_vect *vect, const char *value, size_t count)
{
	return (vect_append_internal(vect, value, count, g_flag_string));
}
