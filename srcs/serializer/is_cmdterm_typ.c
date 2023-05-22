/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_cmdterm_typ.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 08:55:30 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 23:44:29 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"

bool	is_cmdterm(const t_cmdelmarr *elems, t_cmd_elem_type type)
{
	return (get_cmdterm(elems) == type);
}

t_cetyp	get_cmdterm(const t_cmdelmarr *elems)
{
	t_cmd_elem	*elemarr;
	t_cetyp		type;

	elemarr = (t_cmd_elem *)(elems->p);
	type = elemarr[elems->len - 1].type;
	if (type == CMDTYP_OP_AND
		|| type == CMDTYP_OP_OR
		|| type == CMDTYP_PIPE)
		return (type);
	else
		return (CMDTYP_NORMAL);
}
