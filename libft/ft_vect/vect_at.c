/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_at.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 00:23:26 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/28 01:23:28 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_vect.h"

void	*vect_at(const t_vect *vect, size_t index)
{
	unsigned char	*p;

	if (vect->len <= index)
		return (NULL);
	p = vect->p;
	return (p + (vect->elemsize * index));
}
