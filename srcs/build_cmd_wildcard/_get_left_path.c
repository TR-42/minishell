/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _get_left_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:11:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 00:21:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_build_cmd.h"
#include "_filectrl_tools.h"

#include "_build_cmd_wildcard.h"

// !! MUST_PRINT_ERROR_IN_CALLER (malloc error)
__attribute__((nonnull))
bool	get_left_path(
	t_cmd_elem *elems,
	size_t i_wildcard,
	char **buf
)
{
	size_t		tmp;
	t_cmdelmarr	elemarr;

	if (i_wildcard == 0)
		return (true);
	elemarr = (t_cmdelmarr){0};
	elemarr.len = i_wildcard;
	elemarr.elemsize = sizeof(t_cmd_elem);
	elemarr.p = (void *)elems;
	tmp = 0;
	*buf = _get_argv_one(&elemarr, &tmp);
	return (*buf != NULL);
}

// !! MUST_PRINT_ERROR_IN_CALLER (malloc error)
__attribute__((nonnull))
bool	get_right_path(
	t_cmd_elem *elems,
	size_t i_wildcard,
	size_t i_len,
	char **buf
)
{
	size_t		tmp;
	t_cmdelmarr	elemarr;

	if (i_len <= (i_wildcard + 2))
		return (true);
	elems += i_wildcard + 1;
	elemarr = (t_cmdelmarr){0};
	elemarr.len = i_len - i_wildcard - 2;
	elemarr.elemsize = sizeof(t_cmd_elem);
	elemarr.p = (void *)elems;
	tmp = 0;
	*buf = _get_argv_one(&elemarr, &tmp);
	return (*buf != NULL);
}
