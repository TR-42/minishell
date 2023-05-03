/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt_c_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 02:44:07 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/26 21:33:55 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"
#include "../ft_string/ft_string.h"

const char *const	g_nullstr = "(null)";

bool	parse_opt_c_str(char fmt, va_list *args, t_fmt *p_ret)
{
	if (fmt == 'c' || fmt == '%')
	{
		p_ret->type = CHAR;
		if (fmt == 'c')
			p_ret->data.c = (char)va_arg(*args, int);
		else
			p_ret->data.c = '%';
		p_ret->str_len = 1;
	}
	else if (fmt == 's')
	{
		p_ret->type = STR;
		p_ret->data.str = va_arg(*args, char *);
		if (p_ret->data.str == NULL)
			p_ret->data.str = (char *)g_nullstr;
		p_ret->str_len = ft_strlen(p_ret->data.str);
	}
	else
		return (false);
	return (true);
}
