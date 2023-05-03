/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_push_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:30:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/06 23:58:04 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"

bool	vect_push_back(t_vect *vect, const void *elem, size_t *written_index)
{
	size_t	index;

	index = vect->len;
	if (!vect_set(vect, elem, index))
		return (false);
	if (written_index != NULL)
		*written_index = index;
	return (true);
}
