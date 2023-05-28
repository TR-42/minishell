/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ignore_var_in_delimiter.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 15:39:09 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 16:05:35 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serializer.h"
#include "childs.h"
#include "_build_cmd.h"

void	ignore_var_in_delimiter(t_cmdelmarr *elemarr)
{
	size_t		i;
	size_t		i_last;
	t_cmd_elem	*elems;

	i = 0;
	elems = (t_cmd_elem *)(elemarr->p);
	while (i < elemarr->len)
	{
		if (elems[i].type == CMDTYP_RED_HEREDOC
			|| elems[i].type == CMDTYP_RED_HEREDOC_SAVED)
		{
			i_last = i + _one_elem_count(elemarr, i + 1);
			while (++i <= i_last)
			{
				if (is_cetyp_var(elems[i].type))
				{
					elems[i].elem_top -= 1;
					elems[i].len += 1;
				}
				elems[i].type = CMDTYP_NORMAL;
			}
		}
		else
			i++;
	}
}
