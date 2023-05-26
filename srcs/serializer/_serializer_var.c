/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 21:20:51 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

bool	_is_valid_var_char(char c)
{
	return (ft_isalnum(c)
		|| c == '_');
}

static bool	_when_pars_mde_normal(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (**input != '$' || !_is_valid_var_char((*input)[1]))
		return (false);
	*input += 1;
	*mode = M_VAR;
	if (0 < v->len)
	{
		v->nospace = true;
		return (true);
	}
	v->elem_top = *input;
	return (false);
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
		if (!_is_valid_var_char(**input))
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
