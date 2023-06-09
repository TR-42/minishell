/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elems_make_flat.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 11:36:40 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 17:28:12 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - free
#include <stdlib.h>

#include <stdio.h>

#include "ft_mem/ft_mem.h"

#include "_build_cmd.h"
#include "error_utils.h"

// !NO_ERROR
__attribute__((nonnull))
static size_t	_make_flat(t_cmd_elem *dst, t_cmd_elem elem, size_t len)
{
	t_cmd_elem	elem_to_set;
	size_t		i;

	i = 0;
	while (i < len)
	{
		elem_to_set = elem;
		elem_to_set.p_malloced = ((char **)(elem.p_malloced))[i];
		elem_to_set.p_mlc_len = 0;
		elem_to_set.type = CMDTYP_NORMAL;
		if ((i + 1) != len)
			elem_to_set.nospace = false;
		ft_memcpy(dst + i, &elem_to_set, sizeof(t_cmd_elem));
		i++;
	}
	free(elem.p_malloced);
	return (len);
}

// !! ERR_PRINTED
// -> (root) for vect_insert_range
__attribute__((nonnull))
bool	elems_make_flat(t_cmdelmarr *elemarr)
{
	size_t		i;
	t_cmd_elem	elem;

	i = 0;
	while (i < elemarr->len)
	{
		elem = ((t_cmd_elem *)(elemarr->p))[i];
		if (elem.type == CMDTYP_VARIABLE && 0 < elem.p_mlc_len)
		{
			if (!vect_insert_range(elemarr, i, NULL, elem.p_mlc_len - 1))
				return (strerr_ret_false("elems_make_flat"));
			i += _make_flat((t_cmd_elem *)(elemarr->p) + i,
					elem, elem.p_mlc_len);
		}
		else
			i++;
	}
	return (true);
}
