/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:00:01 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:30:14 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_string.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		s1_len;
	const char	*s1_end;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL || *s1 == '\0')
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s1_end = s1 + s1_len - 1;
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	if (*s1 == '\0')
		return (ft_strdup(""));
	while (ft_strchr(set, *s1_end) != NULL)
		s1_end--;
	return (ft_strndup(s1, (size_t)s1_end - (size_t)s1 + 1));
}
