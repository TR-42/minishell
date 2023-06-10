/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:53:48 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 22:28:17 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_exec_builtin.h"
#include "_environ.h"
#include "ft_string/ft_string.h"

#define CD "cd"
#define ECHO "echo"
#define ENV "env"
#define EXIT "exit"
#define EXPORT "export"
#define PWD "pwd"
#define UNSET "unset"

static int	handle_exit(char **argv, int *status);

int	exec_builtin(char **argv, int *exit_status)
{
	if (argv == NULL || *argv == NULL)
		return (-1);
	if (ft_strncmp(*argv, CD, sizeof(CD)) == 0)
		*exit_status = builtin_cd(argv);
	else if (ft_strncmp(*argv, ECHO, sizeof(ECHO)) == 0)
		*exit_status = builtin_echo(argv);
	else if (ft_strncmp(*argv, ENV, sizeof(ENV)) == 0)
		*exit_status = builtin_env(argv);
	else if (ft_strncmp(*argv, EXIT, sizeof(EXIT)) == 0)
		return (handle_exit(argv, *exit_status));
	else if (ft_strncmp(*argv, EXPORT, sizeof(EXPORT)) == 0)
		*exit_status = builtin_export(argv);
	else if (ft_strncmp(*argv, PWD, sizeof(PWD)) == 0)
		*exit_status = builtin_pwd();
	else if (ft_strncmp(*argv, UNSET, sizeof(UNSET)) == 0)
		*exit_status = builtin_unset(argv);
	else
		return (0);
	if (*get_saved_environs() == NULL)
		return (-1);
	return (1);
}

static int	handle_exit(char **argv, int *status)
{
	*status = builtin_exit(argv, *status);
	if (*status <= 0xff)
		return (1);
	*status &= 0xff;
	return (-1);
}

bool	is_builtin(char **argv)
{
	if (argv == NULL || *argv == NULL)
		return (false);
	if (ft_strncmp(*argv, CD, sizeof(CD)) == 0
		|| ft_strncmp(*argv, ECHO, sizeof(ECHO)) == 0
		|| ft_strncmp(*argv, ENV, sizeof(ENV)) == 0
		|| ft_strncmp(*argv, EXIT, sizeof(EXIT)) == 0
		|| ft_strncmp(*argv, EXPORT, sizeof(EXPORT)) == 0
		|| ft_strncmp(*argv, PWD, sizeof(PWD)) == 0
		|| ft_strncmp(*argv, UNSET, sizeof(UNSET)) == 0)
		return (true);
	return (false);
}
