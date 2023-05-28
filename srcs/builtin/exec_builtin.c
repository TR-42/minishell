/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:53:48 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 18:36:31 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_exec_builtin.h"
#include "ft_string/ft_string.h"

#define CD "cd"
#define ECHO "echo"
#define ENV "env"
#define EXIT "exit"
#define EXPORT "export"
#define PWD "pwd"
#define UNSET "unset"

int	exec_builtin(const char **argv, int *exit_status)
{
	if (argv == NULL || *argv == NULL)
		return (-1);
	if (ft_strncmp(*argv, CD) == 0)
		*exit_status = builtin_cd(argv);
	else if (ft_strncmp(*argv, ECHO) == 0)
		*exit_status = builtin_echo(argv);
	else if (ft_strncmp(*argv, ENV) == 0)
		*exit_status = builtin_env(argv);
	else if (ft_strncmp(*argv, EXIT) == 0)
	{
		*exit_status = builtin_exit(argv, *exit_status);
		return (-1);
	}
	else if (ft_strncmp(*argv, EXPORT) == 0)
		*exit_status = builtin_export(argv);
	else if (ft_strncmp(*argv, PWD) == 0)
		*exit_status = builtin_pwd(argv);
	else if (ft_strncmp(*argv, UNSET) == 0)
		*exit_status = builtin_unset(argv);
	else
		return (0);
	return (1);
}
