/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_fp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 05:36:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/27 23:49:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - free
#include <stdlib.h>

#include "ft_mem/ft_mem.h"
#include "ft_string/ft_string.h"

__attribute__((nonnull))
static size_t	count_char(const char *s, int (*is_spc)(int))
{
	size_t	c_count;

	c_count = 0;
	while (*s != '\0')
	{
		if (is_spc(*s))
		{
			while (*s != '\0' && is_spc(*s))
				s++;
			if (*s == '\0')
				break ;
			c_count++;
		}
		else
			s++;
	}
	return (c_count);
}

__attribute__((nonnull))
static int	check_and_handle_alloc_error(char **p_p_ret, size_t p_p_ret_index)
{
	size_t	current_index;

	if (p_p_ret[p_p_ret_index] != NULL)
		return (0 == 1);
	current_index = 0;
	while (current_index < p_p_ret_index)
		free(p_p_ret[current_index++]);
	free(p_p_ret);
	return (0 == 0);
}

__attribute__((nonnull))
char	**ft_split_fp(char const *s, int (*is_spc)(int))
{
	char		**p_p_ret;
	size_t		p_p_ret_index;
	const char	*p_top_to_dup;

	while (*s != '\0' && is_spc(*s))
		s++;
	p_p_ret = ft_calloc(count_char(s, is_spc) + 2, sizeof(void *));
	p_p_ret_index = 0;
	while (p_p_ret != NULL && *s != '\0')
	{
		p_top_to_dup = s;
		while (*s != '\0' && is_spc(*s))
			s++;
		p_p_ret[p_p_ret_index]
			= ft_substr(p_top_to_dup, 0, (size_t)s - (size_t)p_top_to_dup);
		if (check_and_handle_alloc_error(p_p_ret, p_p_ret_index++))
			return (NULL);
		while (*s != '\0' && is_spc(*s))
			s++;
	}
	return (p_p_ret);
}
