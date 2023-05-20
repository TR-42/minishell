/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_t_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:50 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 01:14:08 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "serializer.h"

static void	_vect_dispose(void *vect)
{
	t_cmdelmarr	*elems;
	t_cmd_elem	*elemarr;
	size_t		i;

	elems = (t_cmdelmarr *)vect;
	elemarr = (t_cmd_elem *)(elems->p);
	i = 0;
	while (i < elems->len)
	{
		if (elemarr[i++].type == CMDTYP_RED_HEREDOC_SAVED)
		{
			free((char *)(elemarr[i - 1].elem_top));
			elemarr[i - 1].elem_top = NULL;
		}
	}
	vect_dispose(elems);
}

// return: always 0
int	dispose_t_cmdarr(t_cmdarr *cmd)
{
	if (cmd == NULL)
		return (0);
	vect_dispose_each(cmd, _vect_dispose);
	return (0);
}
