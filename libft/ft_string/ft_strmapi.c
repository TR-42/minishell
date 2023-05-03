/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 07:47:01 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:29:21 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p_ret;
	size_t	index;

	if (s == NULL || *s == '\0')
		return (ft_strdup(""));
	p_ret = ft_strdup(s);
	if (f == NULL || p_ret == NULL)
		return (p_ret);
	index = 0;
	while (*s != '\0')
	{
		p_ret[index] = f(index, *s++);
		index++;
	}
	return (p_ret);
}
