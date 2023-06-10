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
#define OLDFAIL "failure to save `OLDPWD'"
#define PWDFAIL "failure to save `PWD'"

static bool	get_pwd(char *str, int len);

int	builtin_cd(char **argv)
{
	char	oldpath[PATH_MAX + sizeof(OLDPWD)];
	bool	flag;

	flag = true;
	if (*(++argv) == NULL)
		return (print_error(COMMAND, NULL, FEWARGERR, 1));
	else if (*(argv + 1) != NULL)
		return (print_error(COMMAND, NULL, MANYARGERR, 1));
	ft_bzero(oldpath, PATH_MAX + 1);
	ft_strlcpy(oldpath, OLDPWD, sizeof(OLDPWD));
	if (!get_pwd(oldpath, PATH_MAX))
		flag = false;
	if (chdir(*argv) != 0)
		return (print_error(COMMAND, *argv, strerror(errno), 1));
	if (flag && !set_environ(oldpath))
		print_error(COMMAND, NULL, OLDFAIL, 1);
	flag = true;
	ft_strlcpy(oldpath, PWD_ENV, sizeof(PWD_ENV));
	if (getcwd(oldpath + sizeof(PWD_ENV) - 1, PATH_MAX) == NULL)
		flag = false;
	if (flag && !set_environ(oldpath))
		print_error(COMMAND, NULL, PWDFAIL, 1);
	return (0);
}

static bool	get_pwd(char *str, int len)
{
	char	*tmp;

	if (getcwd(str + sizeof(OLDPWD) - 1, len) != NULL)
		return (true);
	tmp = search_environ("PWD");
	if (tmp != NULL)
	{
		ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
		return (true);
	}
	return (false);
}
