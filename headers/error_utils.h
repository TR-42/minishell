/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:27:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 12:53:54 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

// - bool
# include <stdbool.h>

// - pid
# include <unistd.h>

bool	perr_ret_false(const char *str);
bool	strerr_ret_false(const char *str);
bool	strerr_errno_ret_false(const char *str, int _errno);
bool	errstr_ret_false(const char *str1, const char *str2);

bool	print_sig_ret_false(pid_t pid, int sig);

#endif
