/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:59 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 18:34:23 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "_util_commands.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

static bool	check_is_invalid(char *arg);

int	builtin_unset(char **argv)
{
	int	status;

	if (*(++argv) == NULL)
		return (print_error(COMMAND, NULL, ARGERR, 1));
	status = 0;
	while (*argv != NULL)
	{
		if (check_is_invalid(*argv))
		{
			if (status == 0)
				status = print_error(COMMAND, *argv, PARAMERR, 1);
		}
		else if (!remove_environ(*argv))
			status = print_error(COMMAND, *argv, RMENVERR, 1);
		argv ++;
	}
	return (status);
}

static bool	check_is_invalid(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (true);
	while (*arg != '\0')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (true);
		arg++;
	}
	return (false);
}
