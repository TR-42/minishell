/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:58:25 by kfujita           #+#    #+#             */
/*   Updated: 2023/02/09 00:16:18 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"
#include "ft_printf_local.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		written_count;

	va_start(args, format);
	written_count = ft_vprintf(format, &args);
	va_end(args);
	return (written_count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		written_count;

	va_start(args, format);
	written_count = ft_vdprintf(fd, format, &args);
	va_end(args);
	return (written_count);
}

int	ft_vprintf(const char *format, va_list *args)
{
	return (ft_vdprintf(STDOUT_FILENO, format, args));
}

int	ft_vdprintf(int fd, const char *format, va_list *args)
{
	t_list	*list;
	int		written_count;

	if (*format == '\0')
		return (0);
	else if (format[0] != '%' && format[1] == '\0')
		return (write(fd, format, 1));
	list = parse_format(format, args);
	if (list == NULL)
		return (-1);
	written_count = print_all(fd, list);
	ft_lstclear(&list, free);
	return (written_count);
}
