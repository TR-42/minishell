/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:05:48 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 00:34:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

#include "_build_cmd.h"

// !! NO_ERROR
static bool	_is_term_inval_chk(
	const t_cmd_elem *elems,
	bool is_last_cmd,
	size_t i,
	t_cmd_inval_typ *result
)
{
	if (is_cetyp_terminator(elems[i].type))
	{
		if (is_last_cmd)
		{
			*result = CMD_INVAL_OP_NOPAIR;
			return (true);
		}
		else if (i == 0)
		{
			*result = CMD_INVAL_NOCMD;
			return (true);
		}
	}
	return (false);
}

// !! NO_ERROR
__attribute__((nonnull))
static t_cmd_inval_typ	_is_valid_elem(
	const t_cmdelmarr *cmdelemarr,
	const t_cmd_elem *elems,
	bool is_last_cmd)
{
	size_t			i;
	size_t			tmp;
	bool			is_cmd_shown;
	t_cmd_inval_typ	inval_typ;

	i = 0;
	is_cmd_shown = false;
	while (i < cmdelemarr->len)
	{
		if (_is_term_inval_chk(elems, is_last_cmd, i, &inval_typ))
			return (inval_typ);
		tmp = _one_elem_count(cmdelemarr, i);
		if (!is_cetyp_redirect(elems[i].type))
			is_cmd_shown = true;
		else if (tmp == 1)
			return (CMD_INVAL_REDIRECT_NOARG);
		i += tmp;
	}
	if (!is_cmd_shown)
		return (CMD_INVAL_NOCMD);
	return (CMD_INVAL_NO_ERR);
}

// !! NO_ERROR
__attribute__((nonnull))
t_cmd_inval_typ	is_valid_cmd(const t_cmdelmarr *cmdelemarr, bool is_last_cmd)
{
	if (cmdelemarr->len <= 0)
		return (CMD_INVAL_NOCMD);
	return (_is_valid_elem(
			cmdelemarr,
			(t_cmd_elem *)(cmdelemarr->p),
		is_last_cmd)
	);
}
