/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:51:02 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:41:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_mem.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p_s;
	unsigned char	looking_for;

	if (n == 0)
		return (NULL);
	p_s = (unsigned char *)s;
	looking_for = (unsigned char)c;
	while (--n > 0 && *p_s != looking_for)
		p_s++;
	if (*p_s == looking_for)
		return (p_s);
	else
		return (NULL);
}
