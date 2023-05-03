/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_dispose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 01:26:20 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 14:21:52 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"
#include "stdlib.h"

void	vect_dispose(t_vect *vect)
{
	vect->len = 0;
	vect->cap = 0;
	vect->elemsize = 0;
	free(vect->p);
	vect->p = NULL;
}

void	vect_dispose_each(t_vect *vect, void (*disposer)(void *))
{
	size_t	pos;

	pos = 0;
	if (disposer != NULL)
		while (pos < vect->len)
			disposer(vect_at(vect, pos++));
	vect_dispose(vect);
}

static void	ptrarr_disposer(void *ptr)
{
	free(*((void **)ptr));
}

void	vect_dispose_ptrarr(t_vect *vect)
{
	vect_dispose_each(vect, ptrarr_disposer);
}
