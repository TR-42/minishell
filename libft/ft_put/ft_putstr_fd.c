/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 07:57:56 by kfujita           #+#    #+#             */
/*   Updated: 2022/04/26 00:13:47 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "../ft_string/ft_string.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	length;

	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		length = ft_strnlen(s, INT_MAX);
		write(fd, s, length);
		s += length;
	}
}
