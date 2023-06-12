/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:36:10 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 21:33:05 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_string/ft_string.h"
#include "_util_commands.h"
#include "ft_is/ft_is.h"
#include <unistd.h>
#include <limits.h>
#include <stdint.h>

#define COMMAND "export"
#define DECLARE "declare -x "

static bool	print_env_with_declare(char *env);
static bool	check_is_invalid(char *arg);
static bool	is_all_done(char **src, size_t size);
static int	loop_print_envs(char **envs, size_t	size);

int	builtin_export(char **argv)
{
	char	**envs;
	int		errnum;

	envs = *get_saved_environs();
	if (*(++argv) == NULL)
		return (loop_print_envs(envs, get_strslen(envs)));
	errnum = 0;
	while (*argv != NULL)
	{
		if (check_is_invalid(*argv))
			errnum = print_error(COMMAND, *argv, INVALIDERR, 1);
		else if (!set_environ(*argv) && search_environ(*argv) == NULL)
			errnum = print_error(COMMAND, *argv, SETENVERR, 1);
		argv++;
	}
	return (errnum);
}

static int	loop_print_envs(char **envs, size_t	size)
{
	size_t	target_index;
	char	*done;
	size_t	count;
	int		errnum;

	if (envs == NULL || size == 0 || is_all_done(envs, size))
		return (0);
	target_index = 0;
	count = 1;
	while (count < size)
	{
		if (envs[target_index] == NULL || (envs[count] != NULL
				&& ft_strncmp(envs[target_index], envs[count], SIZE_MAX) > 0))
			target_index = count;
		count++;
	}
	if (!print_env_with_declare(envs[target_index]))
		return (1);
	done = envs[target_index];
	envs[target_index] = NULL;
	errnum = loop_print_envs(envs, size);
	envs[target_index] = done;
	return (errnum);
}

static bool	print_env_with_declare(char *env)
{
	char	*tmp;
	bool	flag;

	flag = true;
	flag &= ft_putstr_fd_with_err(DECLARE, STDOUT_FILENO) != 0;
	tmp = ft_strchr(env, '=');
	if (tmp != NULL)
		*tmp = '\0';
	flag &= ft_putstr_fd_with_err(env, STDOUT_FILENO) != 0;
	if (tmp != NULL)
	{
		flag &= ft_putstr_fd_with_err("=\"", STDOUT_FILENO) != 0;
		flag &= ft_putstr_fd_with_err(tmp + 1, STDOUT_FILENO) != 0;
		flag &= ft_putstr_fd_with_err("\"", STDOUT_FILENO) != 0;
		*tmp = '=';
	}
	flag &= ft_putstr_fd_with_err("\n", STDOUT_FILENO) != 0;
	if (!flag)
		print_error(COMMAND, NULL, PRINTFERR, 1);
	return (flag);
}

static bool	is_all_done(char **src, size_t size)
{
	size_t	count;

	count = 0;
	while (count < size)
	{
		if (src[count] != NULL)
			return (false);
		count++;
	}
	return (true);
}

static bool	check_is_invalid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (true);
	while (*arg != '+' && *arg != '=' && *arg != '\0')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (true);
		arg++;
	}
	if (*arg == '+' && *(arg + 1) != '=')
		return (true);
	return (false);
}
