/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_red_fname.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 21:39:43 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/29 21:35:58 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - malloc
// - free
#include <stdlib.h>

#include "ft_mem/ft_mem.h"

#include "error_utils.h"
#include "validator.h"
#include "_build_cmd.h"

// !! NO_ERROR
__attribute__((nonnull))
static bool	_validate_red_fname(const t_cmd_elem *elems, size_t *i,
	size_t oneelem_len)
{
	size_t		j;
	bool		is_val_set;

	is_val_set = false;
	j = 0;
	while (j < oneelem_len)
	{
		if (elems[*i + j].type != CMDTYP_VARIABLE)
			is_val_set = true;
		else if (1 < elems[*i + j].p_mlc_len)
			return (false);
		else if (elems[*i + j].p_malloced != NULL)
			is_val_set = true;
		j++;
	}
	if (!is_val_set)
		return (false);
	*i += oneelem_len - 1;
	return (true);
}

// !! ERR_PRINTED
// -> (root) for malloc failed
__attribute__((nonnull))
static bool	_print_ref_fname_err(const t_cmd_elem *elems, size_t elems_len)
{
	size_t		str_len;
	const char	*top;
	size_t		i;
	char		*buf;

	i = 0;
	top = elems[i].elem_top - 1;
	if (elems[i].type == CMDTYP_QUOTE_VAR)
		top -= 1;
	else if (*top != '\'' && *top != '\"')
		top += 1;
	str_len = (elems[elems_len - 1].elem_top + elems[elems_len - 1].len - top);
	if (elems[elems_len - 1].type != CMDTYP_NORMAL
		&& (top[str_len] == '\'' || top[str_len] == '\"'))
		str_len += 1;
	buf = malloc(str_len + 1);
	if (buf == NULL)
		strerr_ret_false("_print_ref_fname_err()");
	else
		ft_memcpy(buf, top, str_len);
	errstr_ret_false(buf, "ambiguous redirect");
	free(buf);
	return (false);
}

// !! ERR_PRINTED
// -> (root) for validate error
// -> <inherit> _print_ref_fname_err
__attribute__((nonnull))
bool	validate_red_fname(const t_cmdelmarr *elemarr)
{
	t_cmd_elem	*elems;
	size_t		i;
	size_t		oneelem_len;

	elems = (t_cmd_elem *)(elemarr->p);
	i = 0;
	while (i < elemarr->len)
	{
		if (!is_cetyp_redirect(elems[i++].type))
			continue ;
		oneelem_len = _one_elem_count(elemarr, i);
		if (!_validate_red_fname(elems, &i, oneelem_len))
			return (_print_ref_fname_err(elems + i, oneelem_len));
	}
	return (true);
}
