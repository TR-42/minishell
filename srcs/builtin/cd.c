/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:04:37 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 20:02:08 by kitsuki          ###   ########.fr       */
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
#define OLDLEN 7

int	builtin_cd(char **argv)
{
	char	oldpath[PATH_MAX + OLDLEN + 1];

	if (get_strslen(argv) != 2)
		return (print_error(COMMAND, NULL, ARGERR, 1));
	ft_bzero(oldpath, PATH_MAX + 1);
	ft_strlcpy(oldpath, OLDPWD, OLDLEN + 1);
	if (getcwd(oldpath + OLDLEN, PATH_MAX) == NULL)
		return (print_error(COMMAND, NULL, NULL, errno));
	if (chdir(*(++argv)) != 0)
		return (print_error(COMMAND, *argv, NULL, errno));
	if (!set_environ(oldpath))
		return (print_error(COMMAND, NULL, SETENVERR, 1));
	return (0);
}
