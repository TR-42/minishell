/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _gen_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 19:52:09 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/30 20:23:49 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string/ft_string.h"
#include "ft_mem/ft_mem.h"

#include "_env_util.h"
#include "builtin.h"
#include "error_utils.h"
#include "utils.h"

static char	**_malloc_envp_buf(const char **environs)
{
	size_t	i;
	size_t	cnt;
	char	**envp;

	i = 0;
	cnt = 0;
	while (environs != NULL && environs[i] != NULL)
	{
		if (ft_strchr(environs[i++], '=') != NULL)
			cnt++;
	}
	envp = ft_calloc(sizeof(char *), cnt + 1);
	if (envp == NULL)
		strerr_ret_false("malloc_envp_buf()");
	return (envp);
}

static char	**_set_to_envp(const char **environs, char **envp)
{
	size_t	i;

	i = 0;
	while (*environs != NULL)
	{
		if (ft_strchr(*environs, '=') != NULL)
		{
			envp[i] = ft_strdup(*environs);
			if (envp[i++] == NULL)
			{
				strerr_ret_false("gen_envp()");
				return (free_2darr((void ***)&envp));
			}
		}
		environs += 1;
	}
	return (envp);
}

// !! ERR_PRINTED
// -> (root) for get_environs
// -> (root) for ft_strdup (malloc failure)
char	**gen_envp(void)
{
	const char	**environs;
	char		**envp;

	environs = (const char **)get_environs();
	if (environs == NULL)
		errstr_ret_false("get_environs()", "[WARN] environs was NULL");
	envp = _malloc_envp_buf(environs);
	if (envp == NULL || environs == NULL)
		return (envp);
	return (_set_to_envp(environs, envp));
}
