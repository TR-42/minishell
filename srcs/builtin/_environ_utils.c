/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _environ_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:08:46 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/22 02:08:46 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string/ft_string.h"
#include "_environ.h"
#include "_util_commands.h"

char	**search_environ(const char *name)
{
	char	**env;
	size_t	size;

	env = *get_saved_environs();
	if (env == NULL || name == NULL)
		return (NULL);
	while (*env != NULL)
	{
		size = ft_strlen(name);
		if (ft_strncmp(*env, name, size) == 0 && *(*env + size) == '=')
			return (env);
		env++;
	}
	return (NULL);
}

static bool	add_environ(char *src)
{
	char	**src_envs;
	char	**envs;
	size_t	count;

	src_envs = *get_saved_environs();
	envs = (char **)malloc((get_strslen(src_envs) + 2) * sizeof (char *));
	if (envs == NULL)
		return (false);
	count = 0;
	while (src_envs[count++] != NULL)
		envs[count - 1] = src_envs[count - 1];
	envs[count - 1] = ft_strdup(src);
	if (envs[count - 1] == NULL)
	{
		free(envs);
		return (false);
	}
	envs[count] = NULL;
	*get_saved_environs() = envs;
	free(src_envs);
	return (true);
}

bool	set_environ(char *src)
{
	char	**env;
	char	*tmp;

	tmp = ft_strchr(src, '=');
	if (tmp == NULL || *get_saved_environs() == NULL)
		return (false);
	*tmp = '\0';
	env = search_environ(src);
	*tmp = '=';
	if (env == NULL)
		return (add_environ(src));
	tmp = ft_strdup(src);
	if (tmp == NULL)
		return (false);
	free(*env);
	*env = tmp;
	return (true);
}

bool	remove_environ(char *name)
{
	char	**src_envs;
	char	**envs;
	char	**target;
	char	**tmp;

	target = search_environ(name);
	if (name == NULL || target == NULL)
		return (false);
	src_envs = *get_saved_environs();
	envs = (char **)malloc(get_strslen(src_envs) * sizeof (char *));
	if (envs == NULL)
		return (false);
	tmp = envs;
	while (*src_envs != NULL)
	{
		if (*src_envs != target)
			*(tmp++) = *src_envs;
		src_envs++;
	}
	*tmp = NULL;
	free(*get_saved_environs());
	*get_saved_environs() = envs;
	free(target);
	return (true);
}
