/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 19:24:18 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:42:26 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "ft_mem.h"

void	*ft_memset(void *target, int val_to_set, size_t len_to_fill)
{
	unsigned char	*p_c_target;

	p_c_target = target;
	while (len_to_fill-- > 0)
	{
		*p_c_target = (unsigned char)val_to_set;
		p_c_target++;
	}
	return (target);
}
