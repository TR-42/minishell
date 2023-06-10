/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:04:37 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/10 23:39:33 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string/ft_string.h"
#include "ft_mem/ft_mem.h"
#include "_util_commands.h"
#include "_environ.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/param.h>
#include <limits.h>

#ifndef PATH_MAX
# define PATH_MAX MAXPATHLEN
#endif
#define COMMAND "cd"
#define OLDPWD "OLDPWD="
#define PWD_ENV "PWD="

int	builtin_cd(char **argv)
{
	char	oldpath[PATH_MAX + sizeof(OLDPWD)];

	if (*(++argv) == NULL)
		return (print_error(COMMAND, NULL, FEWARGERR, 1));
	else if (*(argv + 1) != NULL)
		return (print_error(COMMAND, NULL, MANYARGERR, 1));
	ft_bzero(oldpath, PATH_MAX + 1);
	ft_strlcpy(oldpath, OLDPWD, sizeof(OLDPWD));
	if (getcwd(oldpath + sizeof(OLDPWD) - 1, PATH_MAX) == NULL)
		return (print_error(COMMAND, NULL, NULL, errno));
	if (chdir(*argv) != 0)
		return (print_error(COMMAND, *argv, NULL, errno));
	if (!set_environ(oldpath))
		return (print_error(COMMAND, NULL, SETENVERR, 1));
	if (getcwd(oldpath + sizeof(PWD_ENV) - 1, PATH_MAX) == NULL)
		return (print_error(COMMAND, NULL, NULL, errno));
	ft_memcpy(oldpath, PWD_ENV, sizeof(PWD_ENV) - 1);
	if (!set_environ(oldpath))
		return (print_error(COMMAND, NULL, SETENVERR, 1));
	return (0);
}

static bool	save_pwd(void)
{
	char	path[PATH_MAX + 1];
	char	*tmp;

	ft_bzero(path, PATH_MAX + 1);
	if (getcwd(path, PATH_MAX) != NULL)
		return (0);
	tmp = search_environ(PWD);
	if (tmp != NULL)
	{
		if (ft_putstr_fd_with_err(*tmp, STDOUT_FILENO) == 0
			|| ft_putstr_fd_with_err("\n", STDOUT_FILENO) == 0)
			return (print_error(COMMAND, NULL, PRINTFERR, 1));
		return (0);
	}
	return (print_error(COMMAND, NULL, FAILERR, 1));
}
