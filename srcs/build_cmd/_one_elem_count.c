/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _one_elem_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:31:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 00:28:42 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_build_cmd.h"

// !! NO_ERR
__attribute__((nonnull))
size_t	_one_elem_count(const t_cmdelmarr *elemarr, size_t i_start)
{
	size_t		i;
	t_cmd_elem	*elem;

	elem = (t_cmd_elem *)(elemarr->p) + i_start;
	i = 0;
	if (is_cetyp_redirect(elem[i].type))
	{
		i++;
		while ((i + i_start) < elemarr->len
			&& is_cetyp_var_or_normal(elem[i].type))
			if (!(elem[i++].nospace))
				break ;
		return (i);
	}
	else if (is_cetyp_terminator(elem[i].type))
		return (1);
	while ((i + i_start) < elemarr->len)
	{
		if (!is_cetyp_var_or_normal(elem[i].type))
			break ;
		i++;
		if (!(elem[i - 1].nospace) || is_cetyp_terminator(elem[i].type))
			break ;
	}
	return (i);
}
