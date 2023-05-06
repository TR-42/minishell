/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/06 13:24:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

bool	_is_valid_var_char(char c)
{
	return (ft_isalnum(c)
		|| c == '$');
}

// return: Elementが終了するかどうか
bool	_serializer_var(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode == M_NORMAL)
	{
		if (**input != '$' || !_is_valid_var_char((*input)[1]))
			return (false);
		*input += 1;
		*mode = M_VAR;
		return (0 < v->len);
	}
	if (*mode == M_VAR || *mode == M_DQUOTE_VAR)
	{
		v->type = CMDTYP_VARIABLE;
		if (*mode == M_DQUOTE_VAR)
			v->type = CMDTYP_QUOTE_VAR;
		if (**input == '$' && 0 < v->len)
		{
			v->nospace = true;
			return (true);
		}
		if (!_is_valid_var_char(**input))
		{
			*mode -= 1;
			return (true);
		}
		v->len += 1;
		*input += 1;
	}
	return (false);
}
