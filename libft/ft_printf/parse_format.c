/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 00:19:18 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/03 20:20:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include "ft_printf_local.h"

t_list	*parse_format(const char *fmt, va_list *args)
{
	t_list	*p_ret;
	size_t	ret_len;

	p_ret = NULL;
	ret_len = 0;
	while (*fmt != '\0' && ret_len < INT_MAX)
	{
		if (*fmt == '%')
			ft_lstadd_back(&p_ret,
				ft_lstnew(parse_opt(&ret_len, (char **)&fmt, args)));
		else
			ft_lstadd_back(&p_ret,
				ft_lstnew(check_no_opt_str(&ret_len, (char **)&fmt, NULL)));
		if (p_ret == NULL || ft_lstlast(p_ret)->content == NULL)
			ret_len = UINTPTR_MAX;
	}
	if (ret_len >= INT_MAX)
		ft_lstclear(&p_ret, free);
	return (p_ret);
}
