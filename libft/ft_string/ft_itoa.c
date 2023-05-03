/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 06:34:36 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:14:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdlib.h>

#define NUM_STR_BUF_LEN (12)

static char	*reverse_str(char *str)
{
	char	*str_top;
	char	*str_end;
	char	tmp;

	if (str == NULL)
		return (NULL);
	str_top = str;
	str_end = str;
	while (*str_end != '\0')
		str_end++;
	str_end -= 1;
	while (str_top < str_end)
	{
		tmp = *str_end;
		*str_end-- = *str_top;
		*str_top++ = tmp;
	}
	return (str);
}

static long	ft_absl(long v)
{
	if (v >= 0)
		return (v);
	else
		return (v * -1);
}

char	*ft_itoa(int n)
{
	char	num_str_buf[NUM_STR_BUF_LEN];
	int		buf_pos;
	long	long_n;

	if (n == 0)
		return (ft_strdup("0"));
	buf_pos = 0;
	long_n = ft_absl(n);
	while (long_n != 0)
	{
		num_str_buf[buf_pos++] = (long_n % 10) + '0';
		long_n /= 10;
	}
	if (n < 0)
		num_str_buf[buf_pos++] = '-';
	num_str_buf[buf_pos] = '\0';
	return (reverse_str(ft_strdup(num_str_buf)));
}
