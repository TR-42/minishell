/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_t_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 18:01:50 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/27 22:28:56 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "serializer.h"

// !! NO_ERROR
__attribute__((nonnull))
static void	_vect_dispose(void *vect)
{
	t_cmdelmarr	*elems;
	t_cmd_elem	*elemarr;
	size_t		i;
	size_t		j;

	elems = (t_cmdelmarr *)vect;
	elemarr = (t_cmd_elem *)(elems->p);
	i = 0;
	while (i < elems->len)
	{
		if (elemarr[i].p_malloced != NULL)
		{
			j = 0;
			while (j < elemarr[i].p_mlc_len)
				free(((char **)(elemarr[i].p_malloced))[j++]);
			free(elemarr[i].p_malloced);
			elemarr[i].p_malloced = NULL;
		}
		i += 1;
	}
	vect_dispose(elems);
}

// return: always 0
// !! NO_ERROR
int	dispose_t_cmdarr(t_cmdarr *cmd)
{
	if (cmd == NULL)
		return (0);
	vect_dispose_each(cmd, _vect_dispose);
	return (0);
}
