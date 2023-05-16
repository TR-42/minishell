/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _env_util.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:39:47 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/08 00:13:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ENV_UTIL_H
# define _ENV_UTIL_H

const char	*get_env_value(char *const envp[], const char *name);
char		**get_path_in_env(char *const envp[]);

#endif
