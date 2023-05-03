/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:48:10 by kfujita           #+#    #+#             */
/*   Updated: 2023/03/02 11:24:24 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sort.h"
#include "../ft_mem/ft_mem.h"

#include "../ft_math/ft_math.h"

// ref: http://www.math.u-ryukyu.ac.jp/~suga/C/2004/13/node6.html

unsigned char	*_at(unsigned char *base, size_t i, size_t memb_size)
{
	return (base + (i * memb_size));
}

void	_ft_qsort(unsigned char *base, size_t nmemb, size_t memb_size,
	t_compar compar)
{
	size_t			i;
	size_t			i_last;

	if (base == NULL || nmemb <= 1 || memb_size <= 0 || compar == NULL)
		return ;
	i = 1;
	i_last = 0;
	while (i < nmemb)
	{
		if (0 < compar(base, _at(base, i, memb_size)))
			ft_swap(_at(base, i, memb_size),
				_at(base, ++i_last, memb_size), memb_size);
		i++;
	}
	ft_swap(base, _at(base, i_last, memb_size), memb_size);
	if (2 <= i_last)
		_ft_qsort(base, i_last, memb_size, compar);
	if (2 <= (nmemb - i_last - 1))
		_ft_qsort(_at(base, i_last + 1, memb_size), nmemb - i_last - 1,
			memb_size, compar);
}

bool	ft_qsort(void *base, size_t nmemb, size_t memb_size, t_compar compar)
{
	if (!can_mulp(nmemb, memb_size))
		return (false);
	_ft_qsort((unsigned char *)base, nmemb, memb_size, compar);
	return (true);
}
