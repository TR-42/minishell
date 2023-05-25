/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:34:59 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 19:32:27 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "_build_cmd.h"

// !! MUST_PRINT_ERROR_IN_CALLER
// -> argcがINT_MAXを超過した場合、argcの生成に失敗するため、`-1`が返る
__attribute__((nonnull))
int	_get_argc(const t_cmdelmarr *elemarr)
{
	size_t			argc;
	size_t			i;
	t_cmd_elem		*elem;

	elem = (t_cmd_elem *)(elemarr->p);
	i = 0;
	argc = 0;
	while (i < elemarr->len)
	{
		if (is_cetyp_var_or_normal(elem[i].type))
			argc++;
		if (INT_MAX <= argc)
			return (-1);
		i += _one_elem_count(elemarr, i);
	}
	return (argc);
}
