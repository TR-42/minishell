/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 00:23:26 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/02 00:32:19 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_is/ft_is.h"

#include "_serializer.h"

// return: Elementが終了するかどうか
__attribute__((nonnull))
bool	_serializer_wildcard(const char **input, t_pars_mde *mode,
	t_cmd_elem *v)
{
	if (*mode != M_NORMAL || **input != '*')
		return (false);
	if (0 < v->len)
		v->nospace = true;
	else
	{
		*input += 1;
		v->len = 1;
		v->type = CMDTYP_VAR_WILDCARD;
		v->nospace = !ft_isspcornil(**input);
	}
	return (true);
}
