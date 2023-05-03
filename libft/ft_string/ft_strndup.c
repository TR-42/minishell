/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:40:31 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:24:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../ft_math/ft_math.h"
#include "ft_string.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	s1_len;
	char	*p_ret;
	char	*p_ret_top;

	if (n <= 0)
		return (ft_strdup(""));
	s1_len = ft_minp(ft_strlen(s1), n);
	p_ret = (char *)malloc(s1_len + 1);
	p_ret_top = p_ret;
	if (p_ret == NULL)
		return (NULL);
	while (s1_len-- > 0)
		*p_ret++ = *s1++;
	*p_ret = '\0';
	return (p_ret_top);
}
