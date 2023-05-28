/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ret_false.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:27:10 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 12:55:16 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - perror
#include <stdio.h>

// - strerror
#include <string.h>

// - STDERR_FILENO
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "error_utils.h"

bool	perr_ret_false(const char *str)
{
	perror(str);
	write(STDERR_FILENO, "\n", 1);
	return (false);
}

bool	strerr_ret_false(const char *str)
{
	return (strerr_errno_ret_false(str, errno));
}

bool	strerr_errno_ret_false(const char *str, int _errno)
{
	return (errstr_ret_false(str, strerror(_errno)));
}

bool	errstr_ret_false(const char *str1, const char *str2)
{
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", str1, str2);
	return (false);
}
