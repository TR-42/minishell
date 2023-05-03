/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 01:27:16 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:23:37 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"
#include "../ft_mem/ft_mem.h"
#include "../ft_math/ft_math.h"

t_fmt	*parse_opt(size_t *len, char **fmt, va_list *args)
{
	t_fmt	*p_ret;

	*fmt += 1;
	if (!is_valid_conv_char(**fmt)
		&& !is_valid_flag_char(**fmt))
		return (check_no_opt_str(len, fmt, NULL));
	p_ret = ft_calloc(1, sizeof(t_fmt));
	if (p_ret == NULL)
		return (p_ret);
	while (is_valid_flag_char(**fmt))
		parse_opt_flags(fmt, p_ret);
	if (!(parse_opt_c_str(**fmt, args, p_ret)
			|| parse_opt_num(**fmt, args, p_ret)
			|| parse_opt_ptr(**fmt, args, p_ret)))
		return (check_no_opt_str(len, fmt, p_ret));
	*fmt += 1;
	*len += ft_max(p_ret->min_len, p_ret->str_len + p_ret->head_len);
	return (p_ret);
}
