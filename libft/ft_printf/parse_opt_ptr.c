/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 02:46:19 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:22:29 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"
#include "../ft_string/ft_string.h"

bool	parse_opt_ptr(char fmt, va_list *args, t_fmt *p_ret)
{
	size_t	num;

	if (fmt != 'p')
		return (false);
	p_ret->type = PTR;
	num = (size_t)va_arg(*args, void *);
	p_ret->header[0] = '0';
	p_ret->header[1] = 'x';
	p_ret->head_len = 2;
	if (num == 0)
	{
		p_ret->str_len = 1;
		p_ret->data.c = '0';
	}
	else
		p_ret->str_len = get_numstr_base(p_ret->data.str_buf, num, 16, false);
	return (true);
}
