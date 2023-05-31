/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd_with_err.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 07:57:56 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/30 23:38:05 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include "ft_string/ft_string.h"

size_t	ft_putstr_fd_with_err(char *s, int fd)
{
	ssize_t	length;
	ssize_t	out;

	if (s == NULL)
		return (0);
	while (*s != '\0')
	{
		length = ft_strnlen(s, INT_MAX);
		out = write(fd, s, length);
		if (out != length)
			return (0);
		s += length;
	}
	return (length);
}
