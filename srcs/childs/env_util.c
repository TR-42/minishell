/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 06:42:05 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 15:21:34 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - bool
#include <stdbool.h>

// - NULL
#include <stddef.h>

#include "ft_string/ft_string.h"

#include "_env_util.h"

static const char	*is_this_requested_env(const char *envp, const char *name,
						size_t name_len);

// !! NO_ERROR (指定の環境変数が見つからなかったときはNULLが返る)
__attribute__((nonnull))
const char	*get_env_value(char *const envp[], const char *name)
{
	return (get_env_value_nlen(envp, name, ft_strlen(name)));
}

// !! NO_ERROR (指定の環境変数が見つからなかったときはNULLが返る)
__attribute__((nonnull))
const char	*get_env_value_nlen(char *const envp[], const char *name,
	size_t name_len)
{
	const char	*p_value;

	p_value = NULL;
	while (*envp != NULL && p_value == NULL)
	{
		p_value = is_this_requested_env(*envp, name, name_len);
		envp++;
	}
	if (p_value != NULL && *p_value == '\0')
		return (NULL);
	return (p_value);
}

// !! NO_ERROR
__attribute__((nonnull))
static const char	*is_this_requested_env(const char *envp, const char *name,
	size_t name_len)
{
	size_t	i;

	i = 0;
	while (envp[i] != '=')
	{
		if (envp[i] == '\0' || i == name_len || envp[i] != name[i])
			return (NULL);
		i++;
	}
	if (i == name_len)
		return (envp + i + 1);
	else
		return (NULL);
}

// !! MUST_PRINT_ERROR_IN_CALLER
// -> EINVAL: 指定の環境変数が見つからなかった
// -> *: ft_splitでのmalloc失敗
char	**get_path_in_env(char *const envp[])
{
	const char	*path;

	if (envp == NULL)
		return (NULL);
	path = get_env_value(envp, "PATH");
	if (path == NULL)
	{
		errno = EINVAL;
		return (NULL);
	}
	return (ft_split(path, ':'));
}
