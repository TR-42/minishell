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

#include "_pwd.h"
#include "ft_printf/ft_printf.h"
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

static bool	copy_pwd(char *str);
static bool change_currentdir(char *arg);
static bool	change_absolute_dir(char *arg);

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
	if (!update_pwd(false) || !copy_pwd(oldpath + sizeof(OLDPWD) - 1))
		flag = false;
	if (!change_currentdir(*argv))
		return (print_error(COMMAND, *argv, strerror(errno), 1));
	if (flag && !set_environ(oldpath))
		print_error(COMMAND, NULL, OLDFAIL, 1);
	ft_memcpy(oldpath, PWD_ENV, sizeof(PWD_ENV));
	if (!update_pwd(false) || !copy_pwd(oldpath + sizeof(PWD_ENV) - 1)
		|| !set_environ(oldpath))
		print_error(COMMAND, NULL, PWDFAIL, 1);
	return (0);
}

static bool	copy_pwd(char *str)
{
	char	*tmp;

	tmp = get_pwd();
	if (tmp == NULL)
		return (false);
	ft_memcpy(str, tmp, ft_strlen(tmp) + 1);
	return (true);
}

static bool change_currentdir(char *arg)
{
	char	**tmp;

	if (*arg == '\0' || chdir(arg) == 0)
		return (true);
	if (*arg == '/')
		return (false);
	if (change_absolute_dir(arg))
		return (true);
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		tmp = search_environ("OLDPWD");
		if (tmp != NULL && ft_strchr(*tmp, '=') != NULL
			&& chdir(ft_strchr(*tmp, '=') + 1) == 0)
		{
			ft_printf("%s\n", ft_strchr(*tmp, '=') + 1);
			return (true);
		}
	}
	return (false);
}

static bool	put_pwd(char *pwd, char *str)
{
	size_t	count;

	if (*str == '\0' || ft_strncmp(str, ".", 2) == 0)
		return (true);
	count = ft_strlen(pwd);
	if (ft_strncmp(str, "..", 3) == 0)
	{
		while (count > 0 && pwd[count] != '/')
			pwd[count--] = '\0';
		if (count > 0)
			pwd[count] = '\0';
		return (true);
	}
	if (count < PATH_MAX && count > 1)
		ft_memcpy((pwd + count++), "/", 1);
	if (count + ft_strlen(str) + 1 >= PATH_MAX)
		return (false);
	ft_memcpy(pwd + count, str, ft_strlen(str) + 1);
	return (true);
}

static bool	change_absolute_dir(char *arg)
{
	char	*getpwd;
	char	pwd[PATH_MAX];
	char	**tmps;
	size_t	count;

	getpwd = get_pwd();
	if (getpwd == NULL)
		return (false);
	tmps = ft_split(arg, '/');
	if (tmps == NULL)
		return (false);
	ft_memcpy(pwd, getpwd, ft_strlen(getpwd) + 1);
	count = 0;
	while (tmps[count] != NULL)
	{
		if (!put_pwd(pwd, tmps[count]))
			break ;
		count++;
	}
	count = get_strslen(tmps) - count;
	free_all(tmps);
	return (count == 0 && chdir(pwd) == 0);
}
