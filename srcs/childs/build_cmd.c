/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 00:34:59 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/11 23:57:39 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

#include "_build_cmd.h"

int	_get_argc(const t_cmdelmarr *elemarr)
{
	size_t			argc;
	size_t			i;
	t_cmd_elem		*elem;
	t_cmd_elem_type	t;

	elem = (t_cmd_elem *)(elemarr->p);
	i = 0;
	argc = 0;
	while (i < elemarr->len)
	{
		t = elem[i].type;
		if (t == CMDTYP_PIPE)
			break ;
		if (t == CMDTYP_RED_IN || t == CMDTYP_RED_OUT || t == CMDTYP_RED_APPEND
			|| t == CMDTYP_RED_HEREDOC)
		{
			t = elem[++i].type;
			if (t == CMDTYP_NORMAL || t == CMDTYP_VARIABLE
				|| t == CMDTYP_QUOTE_VAR)
				i++;
			continue ;
		}
		if (!(elem[i].nospace) || (i + 1) == elemarr->len
			|| elem[i + 1].type == CMDTYP_PIPE)
			argc++;
		if (INT_MAX <= argc)
			return (-1);
		i++;
	}
	return (argc);
}
