/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 02:42:54 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:22:11 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"
#include "../ft_string/ft_string.h"

static int	calc_num_len(long num, int base, t_fmt *p_ret)
{
	char	*buf;

	buf = p_ret->data.str_buf;
	if (p_ret->type == UINT_16BASE)
	{
		if (p_ret->f_hash && num != 0)
			p_ret->header[0] = '0';
	}
	else if (num < 0)
	{
		p_ret->header[0] = '-';
		num *= -1;
	}
	else if (p_ret->f_plus && p_ret->type != UINT_10BASE)
		p_ret->header[0] = '+';
	else if (p_ret->f_space && p_ret->type != UINT_10BASE)
		p_ret->header[0] = ' ';
	p_ret->head_len = ft_strlen(p_ret->header);
	if (num == 0)
	{
		p_ret->data.c = '0';
		return (1);
	}
	return (get_numstr_base(buf, num, base, p_ret->f_upper));
}

static bool	parse_num_type(char fmt, t_fmt *p_ret)
{
	if (fmt == 'd' || fmt == 'i')
		p_ret->type = INT_10BASE;
	else if (fmt == 'u')
		p_ret->type = UINT_10BASE;
	else if (fmt == 'x' || fmt == 'X')
	{
		p_ret->type = UINT_16BASE;
		p_ret->header[1] = fmt;
	}
	else
		return (false);
	return (true);
}

bool	parse_opt_num(char fmt, va_list *args, t_fmt *p_ret)
{
	if (!parse_num_type(fmt, p_ret))
		return (false);
	if (fmt == 'X')
		p_ret->f_upper = true;
	if (p_ret->type == INT_10BASE)
		p_ret->data.s_digit = va_arg(*args, int);
	else
		p_ret->data.s_digit = va_arg(*args, unsigned int);
	if (p_ret->type == INT_10BASE)
		p_ret->str_len = calc_num_len(p_ret->data.s_digit, 10, p_ret);
	else if (p_ret->type == UINT_10BASE)
		p_ret->str_len = calc_num_len(p_ret->data.u_digit, 10, p_ret);
	else
		p_ret->str_len = calc_num_len(p_ret->data.u_digit, 16, p_ret);
	return (true);
}
