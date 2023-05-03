/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 04:49:14 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:15:06 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_mem/ft_mem.h"
#include "ft_string.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*p_ret;

	if (s1 == NULL)
		s1_len = 0;
	else
		s1_len = ft_strlen(s1);
	if (s2 == NULL)
		s2_len = 0;
	else
		s2_len = ft_strlen(s2);
	p_ret = malloc(s1_len + s2_len + 1);
	if (p_ret == NULL)
		return (NULL);
	ft_memmove(p_ret, s1, s1_len);
	ft_memmove(p_ret + s1_len, s2, s2_len);
	p_ret[s1_len + s2_len] = '\0';
	return (p_ret);
}
