/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 23:27:32 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 09:21:04 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_UTILS_H
# define ERROR_UTILS_H

// - bool
# include <stdbool.h>

bool	perr_ret_false(const char *str);
bool	strerr_ret_false(const char *str);
bool	strerr_errno_ret_false(const char *str, int _errno);

#endif
