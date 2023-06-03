/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filectrl_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:18:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 12:58:05 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - free
// - malloc
#include <stdlib.h>

// - strerror
#include <string.h>

// - access
// - X_OK
#include <unistd.h>

#include "ft_string/ft_string.h"
#include "ft_mem/ft_mem.h"
#include "ft_printf/ft_printf.h"

#include "error_utils.h"
#include "utils.h"
#include "_env_util.h"

#include "_filectrl_tools.h"

// !! NO_ERROR
static bool	_print_err(const char *argv_0, int mode)
{
	if (mode == CHK_GET_PATH_ERR_NOCMD)
		return (errstr_ret_false(argv_0, "Command not found"));
	else
		return (strerr_ret_false(argv_0));
}

// !! MUST_PRINT_ERR_IN_CALLER (malloc failure)
__attribute__((nonnull))
static char	*join_path(const char *path1, const char *path2)
{
	size_t	path1_len;
	size_t	path2_len;
	size_t	concat_slash;
	char	*ret;

	path1_len = ft_strlen(path1);
	path2_len = ft_strlen(path2);
	if (path1[path1_len - 1] == '/')
		concat_slash = 0;
	else
		concat_slash = 1;
	ret = malloc(path1_len + concat_slash + path2_len + 1);
	if (ret != NULL)
	{
		ft_memmove(ret, path1, path1_len);
		ft_memmove(ret + path1_len, "/", concat_slash);
		ft_memmove(ret + path1_len + concat_slash, path2, path2_len);
		ret[path1_len + concat_slash + path2_len] = '\0';
	}
	return (ret);
}

// !! ERR_PRINTED
// -> (root) for join_path (malloc failure)
// -> (root) for Command not found
__attribute__((nonnull))
static bool	_search_executable(const char *given_path, char *const *env_path,
	char **dst)
{
	while (*env_path != NULL)
	{
		*dst = join_path(*env_path, given_path);
		if (*dst == NULL)
			return (strerr_ret_false("_search_executable()/malloc"));
		if (access(*dst, X_OK) == 0)
			return (true);
		free(*dst);
		env_path++;
	}
	return (_print_err(given_path, CHK_GET_PATH_ERR_NOCMD));
}

// !! ERR_PRINTED
// -> (root) for arg `given_path` is NULL (= Command not found)
// -> (root) for file(given_path) is not executable (access X_OK)
// -> (root) for strdup (malloc failure)
// -> (root) for arg `envp` is NULL (= Command not found)
// -> <inherit> _search_executable
__attribute__((nonnull(2)))
bool	chk_and_get_fpath(const char *given_path, char **dst, char **envp)
{
	char	**env_path;
	bool	is_success;

	*dst = NULL;
	if (given_path == NULL)
		return (_print_err(given_path, CHK_GET_PATH_ERR_NOCMD));
	else if (*given_path == '\0' || ft_strchr(given_path, '/') != NULL)
	{
		if (access(given_path, X_OK) != 0)
			return (_print_err(given_path, CHK_GET_PATH_ERR_NOFILE));
		*dst = ft_strdup(given_path);
		if (*dst == NULL)
			return (strerr_ret_false(given_path));
		return (true);
	}
	env_path = get_path_in_env(envp);
	if (env_path == NULL)
		return (_print_err(given_path, CHK_GET_PATH_ERR_NOCMD));
	is_success = _search_executable(given_path, env_path, dst);
	free_2darr((void ***)&env_path);
	return (is_success);
}
