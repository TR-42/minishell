/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:36:10 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 20:06:29 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_string/ft_string.h"
#include "_util_commands.h"
#include "ft_is/ft_is.h"
#include <unistd.h>

#define COMMAND "export"
#define DECLARE "declare -x "

static int	print_envs_with_declare(void);
static bool	check_is_invalid(char *arg);

int	builtin_export(char **argv)
{
	int	errnum;

	if (*(++argv) == NULL)
		return (print_envs_with_declare());
	errnum = 0;
	while (*argv != NULL)
	{
		if (check_is_invalid(*argv))
			errnum = print_error(COMMAND, *argv, INVALIDERR, 1);
		else
			set_environ(*argv);
		argv++;
	}
	return (errnum);
}

static int	print_envs_with_declare(void)
{
	char	**envs;
	char	*tmp;
	bool	flag;

	envs = *get_saved_environs();
	if (envs-- == NULL)
		return (0);
	flag = true;
	while (*(++envs) != NULL && flag)
	{
		flag &= ft_putstr_fd_with_err(DECLARE, STDOUT_FILENO) != 0;
		tmp = ft_strchr(*envs, '=');
		if (tmp != NULL)
			*tmp = '\0';
		flag &= ft_putstr_fd_with_err(*envs, STDOUT_FILENO) != 0;
		if (tmp == NULL)
			continue ;
		flag &= ft_putstr_fd_with_err("=\"", STDOUT_FILENO) != 0;
		flag &= ft_putstr_fd_with_err(tmp + 1, STDOUT_FILENO) != 0;
		flag &= ft_putstr_fd_with_err("\"", STDOUT_FILENO) != 0;
		*tmp = '=';
	}
	if (!flag)
		return (print_error(COMMAND, NULL, PRINTFERR, 1));
	return (0);
}

static bool	check_is_invalid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (true);
	while (*arg != '=' && *arg != '\0')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (true);
		arg++;
	}
	return (false);
}
