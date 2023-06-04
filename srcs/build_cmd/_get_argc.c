/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_argc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:34:59 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 19:32:27 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "_build_cmd.h"

// !! NO_ERROR
__attribute__((nonnull))
bool	_is_value_exists(
	const t_cmd_elem *elems,
	size_t len
)
{
	size_t	i;

	if (!is_cetyp_var_or_normal(elems->type))
		return (false);
	i = 0;
	while (i < len)
	{
		if (elems[i].type == CMDTYP_NORMAL
			|| elems[i].type == CMDTYP_QUOTE_VAR)
			return (true);
		if (elems[i].p_malloced != NULL)
			return (true);
		i += 1;
	}
	return (false);
}

// !! MUST_PRINT_ERROR_IN_CALLER
// -> argcがINT_MAXを超過した場合、argcの生成に失敗するため、`-1`が返る
__attribute__((nonnull))
int	_get_argc(const t_cmdelmarr *elemarr)
{
	size_t			argc;
	size_t			i;
	size_t			len;
	t_cmd_elem		*elem;

	elem = (t_cmd_elem *)(elemarr->p);
	i = 0;
	argc = 0;
	while (i < elemarr->len)
	{
		len = _one_elem_count(elemarr, i);
		if (_is_value_exists(elem + i, len))
			argc += 1;
		if (INT_MAX <= argc)
			return (-1);
		i += len;
	}
	return (argc);
}
