/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 14:54:20 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/11 22:42:36 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*p_c_found;

	p_c_found = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			p_c_found = s;
		s++;
	}
	if (p_c_found != NULL)
		return ((char *)p_c_found);
	else if (c == '\0')
		return ((char *)s);
	else
		return (NULL);
}
