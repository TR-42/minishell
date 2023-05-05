/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_dquote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/05 23:12:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

// return: Elementが終了するかどうか
bool	_serializer_dquote(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_DQUOTE)
	{
		if (*mode != M_NORMAL || **input != '\"')
			return (false);
		*mode = M_DQUOTE;
		*input += 1;
		v->elem_top = *input;
		return (false);
	}
	if (**input == '\"' || (**input == '$' && !ft_isspace((*input)[1])))
	{
		*mode = M_NORMAL;
		if (**input == '$')
			*mode = M_DQUOTE_VAR;
		v->nospace = !ft_isspace(*(++(*input)));
		return (true);
	}
	v->len += 1;
	*input += 1;
	return (false);
}
