/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/26 23:32:52 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

bool	_is_valid_var_char(char c, bool is_first)
{
	if (is_first && c == '?')
		return (true);
	return (ft_isalnum(c)
		|| c == '_');
}

bool	_is_special_var_chk(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (**input == '?')
	{
		*input += 1;
		v->len = 1;
		v->nospace = !ft_isspcornil(**input);
		if (*mode == M_DQUOTE_VAR && **input == '"')
		{
			*mode = M_NORMAL;
			*input += 1;
		}
		else
			*mode -= 1;
		return (true);
	}
	return (false);
}

static bool	_when_pars_mde_normal(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (**input != '$' || !_is_valid_var_char((*input)[1], true))
		return (false);
	*input += 1;
	*mode = M_VAR;
	if (0 < v->len)
	{
		v->nospace = true;
		return (true);
	}
	v->type = CMDTYP_VARIABLE;
	v->elem_top = *input;
	return (_is_special_var_chk(input, mode, v));
}

// return: Elementが終了するかどうか
bool	_serializer_var(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode == M_NORMAL)
		return (_when_pars_mde_normal(input, mode, v));
	if (*mode == M_VAR || *mode == M_DQUOTE_VAR)
	{
		v->type = CMDTYP_VARIABLE;
		if (*mode == M_DQUOTE_VAR)
			v->type = CMDTYP_QUOTE_VAR;
		if (v->len == 0 && _is_special_var_chk(input, mode, v))
			return (true);
		if (!_is_valid_var_char(**input, false))
		{
			if (*mode == M_DQUOTE_VAR && **input == '"')
			{
				*mode = M_NORMAL;
				*input += 1;
			}
			else
				*mode -= 1;
			v->nospace = (*mode == M_DQUOTE || !ft_isspcornil(**input));
			return (true);
		}
		v->len += 1;
		*input += 1;
	}
	return (false);
}
