/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 01:13:22 by kfujita           #+#    #+#             */
/*   Updated: 2023/01/30 16:56:38 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf_local.h"
#include "../ft_math/ft_math.h"

static int	calc_pad_zero_len(t_fmt *fmt, int *pad_len, int *zero_len)
{
	int	expected_print_len;

	if (fmt->f_dot && fmt->max_len == 0 && fmt->data.c == '0')
		fmt->str_len = 0;
	expected_print_len = ft_max(fmt->min_len,
			ft_max(fmt->max_len, fmt->str_len) + fmt->head_len);
	*pad_len = expected_print_len - fmt->str_len - fmt->head_len;
	*zero_len = 0;
	if (fmt->f_dot)
	{
		*zero_len = ft_max(0, fmt->max_len - fmt->str_len);
		*pad_len = ft_max(0, *pad_len - *zero_len);
	}
	else if (!(fmt->f_minus) && fmt->f_zero)
	{
		*zero_len = ft_max(0, fmt->min_len - fmt->str_len - fmt->head_len);
		*pad_len = 0;
	}
	return (expected_print_len);
}

static int	print_buf(int dstfd, t_fmt *fmt)
{
	int	pad_len;
	int	zero_len;
	int	print_len;

	print_len = calc_pad_zero_len(fmt, &pad_len, &zero_len);
	while (!(fmt->f_minus) && pad_len-- > 0)
		write(dstfd, " ", 1);
	write(dstfd, fmt->header, fmt->head_len);
	while (zero_len-- > 0)
		write(dstfd, "0", 1);
	write(dstfd, fmt->data.str_buf, fmt->str_len);
	while (fmt->f_minus && pad_len-- > 0)
		write(dstfd, " ", 1);
	return (print_len);
}

static int	print_char(int dstfd, t_fmt *fmt)
{
	int		pad_len;

	pad_len = fmt->min_len - 1;
	if (fmt->f_minus || !(fmt->f_zero))
	{
		while (!(fmt->f_minus) && pad_len-- > 0)
			write(dstfd, " ", 1);
		write(dstfd, fmt->data.str_buf, 1);
		while (fmt->f_minus && pad_len-- > 0)
			write(dstfd, " ", 1);
	}
	else
	{
		while (pad_len-- > 0)
			write(dstfd, "0", 1);
		write(dstfd, fmt->data.str_buf, 1);
	}
	return (ft_max(fmt->str_len + fmt->head_len, fmt->min_len));
}

static int	print_str(int dstfd, t_fmt *fmt)
{
	int	pad_len;
	int	print_len;

	print_len = fmt->str_len;
	if (fmt->f_dot)
		print_len = ft_min(fmt->max_len, print_len);
	pad_len = fmt->min_len - print_len;
	if (fmt->f_minus || !(fmt->f_zero))
	{
		while (!(fmt->f_minus) && pad_len-- > 0)
			write(dstfd, " ", 1);
		write(dstfd, fmt->data.str, print_len);
		while (fmt->f_minus && pad_len-- > 0)
			write(dstfd, " ", 1);
	}
	else
	{
		while (pad_len-- > 0)
			write(dstfd, "0", 1);
		write(dstfd, fmt->data.str, print_len);
	}
	return (ft_max(print_len, fmt->min_len));
}

int	print_all(int dstfd, t_list *list)
{
	int		written_count;
	int		tmp;
	t_fmt	*data;

	written_count = 0;
	while (list != NULL)
	{
		data = list->content;
		tmp = 0;
		if (data->type == STR)
			tmp = print_str(dstfd, data);
		else if (data->type == CHAR)
			tmp = print_char(dstfd, data);
		else
			tmp = print_buf(dstfd, data);
		written_count += tmp;
		list = list->next;
	}
	return (written_count);
}
