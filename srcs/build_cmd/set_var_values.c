/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:39:39 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 14:44:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"
#include "ft_string/ft_string.h"

#include "_build_cmd.h"
#include "_env_util.h"
#include "error_utils.h"

static bool	_set_var_value_and_split(t_cmd_elem *elem, const char *value)
{
	char		**ret;
	size_t		i;
	bool		contains_spc;

	i = 0;
	contains_spc = false;
	while (elem->type == CMDTYP_VARIABLE && !contains_spc && value[i] != '\0')
		contains_spc = ft_isspace(value[i++]);
	if (!contains_spc)
	{
		elem->p_malloced = ft_strdup(value);
		return (elem->p_malloced != NULL);
	}
	ret = ft_split_fp(value, ft_isspace);
	if (ret == NULL)
		return (false);
	while (ret[elem->p_mlc_len] != NULL)
		elem->p_mlc_len += 1;
	elem->p_malloced = (char *)ret;
	return (true);
}

__attribute__((nonnull))
static bool	_set_var_value(t_cmd_elem *elem, char *const *envp, int exit_stat)
{
	const char	*value;

	if (*(elem->elem_top) == '?')
	{
		elem->p_malloced = ft_itoa(exit_stat);
		return (elem->p_malloced != NULL);
	}
	value = get_env_value_nlen(envp, elem->elem_top, elem->len);
	if (value == NULL)
		return (true);
	return (_set_var_value_and_split(elem, value));
}

// !! ERR_PRINTED
// -> (root) for malloc failed
__attribute__((nonnull))
bool	set_var_values(t_cmdelmarr *elemarr, char *const *envp, int exit_stat)
{
	size_t		i;
	t_cmd_elem	*elems;

	i = 0;
	elems = (t_cmd_elem *)(elemarr->p);
	while (i < elemarr->len)
	{
		if (elems[i].type == CMDTYP_VARIABLE
			|| elems[i].type == CMDTYP_QUOTE_VAR)
		{
			if (!_set_var_value(elems + i, envp, exit_stat))
				return (strerr_ret_false("_set_var_values()"));
		}
		i++;
	}
	return (true);
}
