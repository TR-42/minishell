/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:47 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 16:30:19 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "ft_string/ft_string.h"
#include "_util_commands.h"
#include <stdbool.h>
#include <unistd.h>

#define COMMAND "echo"

int	builtin_echo(char **argv)
{
	bool	flag;
	bool	is_option_n;

	is_option_n = false;
	argv++;
	while (*argv != NULL && ft_strncmp(*argv, "-n", 3) == 0)
	{
		is_option_n = true;
		argv++;
	}
	flag = true;
	while (*argv != NULL && *(argv + 1) != NULL)
	{
		flag &= ft_putstr_fd_with_err(*argv, STDOUT_FILENO) != 0;
		flag &= ft_putstr_fd_with_err(" ", STDOUT_FILENO) != 0;
		argv++;
	}
	if (*argv != NULL)
		flag &= ft_putstr_fd_with_err(*argv, STDOUT_FILENO) != 0;
	if (!is_option_n)
		flag &= ft_putstr_fd_with_err("\n", STDOUT_FILENO) != 0;
	if (!flag)
		return (print_error(COMMAND, NULL, PRINTFERR, 1));
	return (0);
}
