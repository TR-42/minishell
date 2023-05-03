/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 16:50:25 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:29:28 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (--n > 0 && *s1 == *s2 && *s1 != '\0')
	{
		s1++;
		s2++;
	}
	return (*((unsigned char *)s1) - *((unsigned char *)s2));
}
