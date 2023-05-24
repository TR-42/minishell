/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ret_false.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:27:10 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 09:20:53 by kfujita          ###   ########.fr       */
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
	const char	*err_msg;

	err_msg = strerror(errno);
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", str, err_msg);
	return (false);
}

bool	strerr_errno_ret_false(const char *str, int _errno)
{
	const char	*err_msg;

	err_msg = strerror(_errno);
	ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n", str, err_msg);
	return (false);
}
