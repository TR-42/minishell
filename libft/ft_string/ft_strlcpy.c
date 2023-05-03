/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:06:03 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:29:07 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_size;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	if ((src_size + 1) < size)
		size = src_size + 1;
	while (--size > 0)
		*(dest++) = *(src++);
	*dest = '\0';
	return (src_size);
}
