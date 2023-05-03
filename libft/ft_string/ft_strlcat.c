/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 20:11:16 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:28:16 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dest_len;

	dest_len = ft_strnlen(dest, size);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (size + src_len);
	size -= dest_len;
	dest += dest_len;
	while (*src != '\0' && --size > 0)
		*(dest++) = *(src++);
	*dest = '\0';
	return (src_len + dest_len);
}
