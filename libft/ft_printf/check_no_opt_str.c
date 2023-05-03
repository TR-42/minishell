/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_no_opt_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 03:07:49 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:21:26 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include "ft_printf_local.h"
#include "../ft_mem/ft_mem.h"
#include "../ft_math/ft_math.h"

t_fmt	*check_no_opt_str(size_t *len, char **fmt, t_fmt *p_ret)
{
	size_t	str_len;

	str_len = 0;
	if (p_ret == NULL)
		p_ret = ft_calloc(1, sizeof(t_fmt));
	if (p_ret == NULL)
		return (p_ret);
	p_ret->type = STR;
	p_ret->data.str = *fmt;
	while (*len <= INT_MAX && **fmt != '\0' && **fmt != '%')
	{
		str_len++;
		*len += 1;
		*fmt += 1;
	}
	if (*len > INT_MAX)
	{
		free(p_ret);
		return (NULL);
	}
	p_ret->str_len = (int)str_len;
	*len += ft_max(p_ret->min_len, p_ret->str_len);
	return (p_ret);
}
