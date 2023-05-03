/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_numstr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 02:10:07 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/25 23:34:34 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include "ft_string.h"

int	get_numstr_base(char *buf, size_t num, int base, bool is_upper)
{
	int		tmp;
	int		last_len;
	char	c;

	if (num == 0)
		return (0);
	last_len = get_numstr_base(buf, num / base, base, is_upper);
	tmp = num % base;
	if (tmp < 10)
		c = '0' + tmp;
	else if (is_upper)
		c = 'A' + tmp - 10;
	else
		c = 'a' + tmp - 10;
	buf[last_len] = c;
	return (last_len + 1);
}
