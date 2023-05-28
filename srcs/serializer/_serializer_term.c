/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_term.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:30:08 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 00:09:07 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_serializer.h"

// return: Elementが終了するかどうか
__attribute__((nonnull))
bool	_serializer_term(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_NORMAL
		|| !(**input == '|' || (**input == '&' && *(*input + 1) == '&')))
		return (false);
	if (0 < v->len)
		return (true);
	v->type = CMDTYP_PIPE;
	if (**input == '&')
		v->type = CMDTYP_OP_AND;
	else if (*(*input + 1) == '|')
		v->type = CMDTYP_OP_OR;
	v->len = 1;
	if (v->type != CMDTYP_PIPE)
		v->len += 1;
	*input += v->len;
	return (true);
}
