/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_squote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/05 23:12:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

// return: Elementが終了するかどうか
__attribute__((nonnull))
bool	_serializer_squote(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_SQUOTE)
	{
		if (*mode != M_NORMAL || **input != '\'')
			return (false);
		*mode = M_SQUOTE;
		*input += 1;
		v->elem_top = *input;
		return (false);
	}
	if (**input == '\'')
	{
		*mode = M_NORMAL;
		v->nospace = !ft_isspace(*(++(*input)));
		return (true);
	}
	v->len += 1;
	*input += 1;
	return (false);
}
