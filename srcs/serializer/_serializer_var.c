/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_var.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 21:00:06 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/06 11:18:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

// return: Elementが終了するかどうか
bool	_serializer_var(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode == M_NORMAL)
	{
		if (**input != '$' || ft_isspcornil((*input)[1]))
			return (false);
		*input += 1;
		*mode = M_VAR;
		return (0 < v->len);
	}
	if (*mode == M_VAR || *mode == M_DQUOTE_VAR)
	{
		v->type = CMDTYP_VARIABLE;
		if (**input == '$')
		{
			v->nospace = true;
			return (true);
		}
		if (ft_isspcornil(**input))
		{
			*mode -= 1;
			return (true);
		}
		v->len += 1;
		*input += 1;
	}
	return (false);
}
