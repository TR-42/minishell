/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_dquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/06 11:54:15 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

static bool	_when_mode_is_not_dquote(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (*mode != M_NORMAL || **input != '\"')
		return (false);
	*mode = M_DQUOTE;
	*input += 1;
	v->elem_top = *input;
	return (false);
}

// return: Elementが終了するかどうか
bool	_serializer_dquote(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_DQUOTE)
		return (_when_mode_is_not_dquote(input, mode, v));
	if (**input == '\"')
	{
		*mode = M_NORMAL;
		v->nospace = !ft_isspace(*(++(*input)));
		return (true);
	}
	if (**input == '$' && _is_valid_var_char((*input)[1]))
	{
		*mode = M_DQUOTE_VAR;
		v->nospace = !ft_isspace(*(++(*input)));
		if (0 < v->len)
			return (true);
		v->elem_top = *input;
		return (false);
	}
	v->len += 1;
	*input += 1;
	return (false);
}
