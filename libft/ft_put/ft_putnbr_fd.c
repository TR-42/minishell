/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 08:00:42 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:13:30 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "ft_put.h"

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

void	ft_putnbr_fd(int n, int fd)
{
	char	num_str_buf[NUM_STR_BUF_LEN];
	int		buf_pos;
	long	long_n;

	if (0 <= n && n <= 9)
	{
		ft_putchar_fd('0' + n, fd);
		return ;
	}
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
	ft_putstr_fd(reverse_str(num_str_buf), fd);
}
