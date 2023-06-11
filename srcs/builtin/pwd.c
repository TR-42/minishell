/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:16:51 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/10 23:33:29 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_pwd.h"
#include "_environ.h"
#include "_util_commands.h"
#include "ft_printf/ft_printf.h"
#include "ft_mem/ft_mem.h"
#include "ft_string/ft_string.h"
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
#define PWD		"PWD"

int	builtin_pwd(void)
{
	char	*tmp;

	update_pwd(false);
	tmp = get_pwd();
	if (tmp != NULL)
	{
		if (ft_putstr_fd_with_err(tmp, STDOUT_FILENO) == 0
			|| ft_putstr_fd_with_err("\n", STDOUT_FILENO) == 0)
			return (print_error(COMMAND, NULL, PRINTFERR, 1));
		return (0);
	}
	return (print_error(COMMAND, NULL, FAILERR, 1));
}
