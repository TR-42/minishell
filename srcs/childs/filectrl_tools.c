/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filectrl_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:18:27 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 23:17:25 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - free
// - malloc
#include <stdlib.h>

// - access
// - X_OK
#include <unistd.h>

#include "ft_string/ft_string.h"
#include "ft_mem/ft_mem.h"

#include "_filectrl_tools.h"

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

static int	_search_executable(const char *given_path, char *const *env_path,
	char **dst)
{
	while (*env_path != NULL)
	{
		*dst = join_path(*env_path, given_path);
		if (access(*dst, X_OK) == 0)
			return (CHK_GET_PATH_ERR_OK);
		free(*dst);
		env_path++;
	}
	return (CHK_GET_PATH_ERR_NOCMD);
}

int	chk_and_get_fpath(const char *given_path, char *const *env_path, char **dst)
{
	*dst = NULL;
	if (given_path == NULL)
		return (CHK_GET_PATH_ERR_NOCMD);
	else if (*given_path == '\0' || ft_strchr(given_path, '/') != NULL)
	{
		if (access(given_path, X_OK) != 0)
			return (CHK_GET_PATH_ERR_NOFILE);
		*dst = ft_strdup(given_path);
		return (CHK_GET_PATH_ERR_OK);
	}
	else if (env_path == NULL)
		return (CHK_GET_PATH_ERR_NOCMD);
	else
		return (_search_executable(given_path, env_path, dst));
}
