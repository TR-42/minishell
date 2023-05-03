/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_flag_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 22:20:42 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:22:59 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_local.h"
#include "../ft_is/ft_is.h"

bool	is_valid_flag_char(char c)
{
	return (c == '-' || ft_isdigit(c) || c == '.'
		|| c == '#' || c == ' ' || c == '+');
}
