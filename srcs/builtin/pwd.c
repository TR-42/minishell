/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:16:51 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 19:35:54 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_util_commands.h"
#include "ft_printf/ft_printf.h"
#include "ft_mem/ft_mem.h"
#include <sys/param.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>

#ifndef PATH_MAX
# define PATH_MAX MAXPATHLEN
#endif
#define COMMAND "pwd"

int	builtin_pwd(void)
{
	char	path[PATH_MAX + 1];

	ft_bzero(path, PATH_MAX + 1);
	if (getcwd(path, PATH_MAX) != NULL)
	{
		if (ft_putstr_fd_with_err(path, STDOUT_FILENO) == 0
			|| ft_putstr_fd_with_err("\n", STDOUT_FILENO) == 0)
			return (print_error(COMMAND, NULL, PRINTFERR, 1));
		return (0);
	}
	return (print_error(COMMAND, NULL, NULL, errno));
}
