/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 03:37:57 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:24:01 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_printf_local.h"
#include "../ft_is/ft_is.h"
#include "../ft_string/ft_string.h"

static void	parse_opt_flag_dot(char **fmt, t_fmt *p_ret)
{
	long	tmp;

	*fmt += 1;
	p_ret->f_dot = true;
	p_ret->max_len = 0;
	if (!ft_isdigit(**fmt))
		return ;
	tmp = ft_strtol(*fmt, fmt, 10);
	if (tmp > (long)INT_MAX)
		p_ret->max_len = INT_MAX;
	else
		p_ret->max_len = tmp;
}

static void	parse_opt_flag_min_len(char **fmt, t_fmt *p_ret)
{
	long	tmp;

	tmp = ft_strtol(*fmt, fmt, 10);
	if (tmp > (long)INT_MAX)
		p_ret->min_len = INT_MAX;
	else
		p_ret->min_len = tmp;
}

void	parse_opt_flags(char **fmt, t_fmt *p_ret)
{
	if (**fmt == '-')
		p_ret->f_minus = true;
	else if (**fmt == '0')
		p_ret->f_zero = true;
	else if (**fmt == '.')
	{
		parse_opt_flag_dot(fmt, p_ret);
		return ;
	}
	else if (**fmt == '#')
		p_ret->f_hash = true;
	else if (**fmt == ' ')
		p_ret->f_space = true;
	else if (**fmt == '+')
		p_ret->f_plus = true;
	else
	{
		parse_opt_flag_min_len(fmt, p_ret);
		return ;
	}
	*fmt += 1;
}
