/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 23:57:34 by kfujita           #+#    #+#             */
/*   Updated: 2023/03/02 11:23:36 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"

void	_ft_swap(unsigned char *a, unsigned char *b, size_t bytes)
{
	unsigned char	tmp;

	if (a == NULL || b == NULL || a == b)
		return ;
	while (0 < bytes)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
		a++;
		b++;
		bytes--;
	}
}

void	ft_swap(void *a, void *b, size_t bytes)
{
	_ft_swap(a, b, bytes);
}
