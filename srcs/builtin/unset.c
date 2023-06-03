/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:59 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 18:49:47 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "_util_commands.h"
#include "ft_printf/ft_printf.h"
#include "ft_is/ft_is.h"
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define COMMAND "unset"

static bool	check_is_invalid(char *arg);

int	builtin_unset(char **argv)
{
	int	status;

	status = 0;
	while (*(++argv) != NULL)
	{
		if (check_is_invalid(*argv))
		{
			if (status == 0)
				status = print_error(COMMAND, *argv, INVALIDERR, 1);
		}
		else if (!remove_environ(*argv) && search_environ(*argv) != NULL)
			status = print_error(COMMAND, *argv, RMENVERR, 1);
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
