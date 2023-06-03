/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_ret_null.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:27:10 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 16:19:20 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

#include "error_utils.h"

void	*perr_ret_null(const char *str)
{
	perr_ret_false(str);
	return (NULL);
}

void	*strerr_ret_null(const char *str)
{
	strerr_ret_false(str);
	return (NULL);
}

void	*strerr_errno_ret_null(const char *str, int _errno)
{
	strerr_errno_ret_false(str, _errno);
	return (NULL);
}

void	*errstr_ret_null(const char *str1, const char *str2)
{
	errstr_ret_false(str1, str2);
	return (NULL);
}
