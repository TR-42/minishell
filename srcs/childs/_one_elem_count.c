/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _one_elem_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 19:31:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 21:11:51 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_build_cmd.h"

size_t	_one_elem_count(const t_cmdelmarr *elemarr, size_t i_start)
{
	size_t		i;
	t_cmd_elem	*elem;

	elem = (t_cmd_elem *)(elemarr->p) + i_start;
	i = 0;
	if (is_cetyp_redirect(elem[i].type))
	{
		i++;
		while (is_cetyp_var_or_normal(elem[i].type))
			if (!(elem[i++].nospace))
				break ;
		return (i);
	}
	else if (elem[i].type == CMDTYP_PIPE)
		return (1);
	while ((i + i_start) < elemarr->len)
	{
		if (!is_cetyp_var_or_normal(elem[i].type))
			break ;
		i++;
		if (!(elem[i - 1].nospace) || elem[i].type == CMDTYP_PIPE)
			break ;
	}
	return (i);
}
