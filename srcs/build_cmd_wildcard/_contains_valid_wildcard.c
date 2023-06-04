/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _contains_valid_wildcard.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:08:37 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 00:09:09 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_build_cmd_wildcard.h"

#include "serializer.h"

// !! NO_ERROR
__attribute__((nonnull))
bool	_contains_valid_wildcard(
	t_cmd_elem *elems,
	size_t i_start,
	size_t i_next,
	size_t	*wildcard_index
)
{
	bool	contains_wildcard;
	bool	contains_multival_var;

	contains_wildcard = false;
	contains_multival_var = false;
	while (i_start < i_next)
	{
		if (elems[i_start].type == CMDTYP_VAR_WILDCARD)
		{
			*wildcard_index = i_start;
			contains_wildcard = true;
		}
		else if (elems[i_start].type == CMDTYP_VARIABLE
			&& 1 < elems[i_start].p_mlc_len)
			contains_multival_var = true;
		if (contains_wildcard && contains_multival_var)
		{
			elems[*wildcard_index].type = CMDTYP_NORMAL;
			return (false);
		}
		i_start += 1;
	}
	return (contains_wildcard);
}
