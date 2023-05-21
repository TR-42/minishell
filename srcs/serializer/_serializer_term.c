/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _serializer_term.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 23:30:08 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 23:30:29 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_serializer.h"

// return: Elementが終了するかどうか
bool	_serializer_term(const char **input, t_pars_mde *mode, t_cmd_elem *v)
{
	if (*mode != M_NORMAL || **input != '|')
		return (false);
	if (0 < v->len)
		return (true);
	v->type = CMDTYP_PIPE;
	v->len = 1;
	*input += 1;
	return (true);
}
