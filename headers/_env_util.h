/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:39:47 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 00:07:09 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENV_UTIL_H
# define _ENV_UTIL_H

const char	*get_env_value(char *const envp[], const char *name)
			__attribute__((nonnull));
char		**get_path_in_env(char *const envp[])
			__attribute__((nonnull));
const char	*get_env_value_nlen(char *const envp[], const char *name,
				size_t name_len)
			__attribute__((nonnull));

#endif
