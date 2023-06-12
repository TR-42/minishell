/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 08:19:03 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/11 08:19:03 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string/ft_string.h"
#include "_environ.h"
#include "ft_mem/ft_mem.h"
#include <string.h>
#include <stdbool.h>
#include <sys/param.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PATH_MAX
# define PATH_MAX MAXPATHLEN
#endif

static char	**save_pwd(void)
{
	static char	*pwd = NULL;

	return (&pwd);
}

void	dispose_pwd(void)
{
	if (*save_pwd() != NULL)
		free(*save_pwd());
}

static bool	set_pwd(char *src)
{
	if (src == NULL)
		return (false);
	dispose_pwd();
	*save_pwd() = src;
	return (true);
}

bool	update_pwd(bool is_use_env)
{
	char	**pwd;
	char	*tmp;

	tmp = (char *)ft_calloc(PATH_MAX + 1, sizeof(char));
	if (tmp != NULL)
	{
		if (getcwd(tmp, PATH_MAX) != NULL)
			return (set_pwd(tmp));
		else
			free(tmp);
	}
	if (!is_use_env)
		return (false);
	pwd = search_environ("PWD");
	if (pwd != NULL && ft_strchr(*pwd, '=') != NULL)
	{
		tmp = ft_strdup(ft_strchr(*pwd, '=') + 1);
		return (set_pwd(tmp));
	}
	return (false);
}

char	*get_pwd(void)
{
	char	**tmp;

	if (*save_pwd() != NULL)
		return (*save_pwd());
	tmp = search_environ("PWD");
	if (tmp != NULL && ft_strchr(*tmp, '=') != NULL)
		return (ft_strchr(*tmp, '=') + 1);
	return (NULL);
}
