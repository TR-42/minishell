/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:47 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/20 20:53:47 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "ft_string/ft_string.h"
#include "_util_commands.h"
#include <stdbool.h>

#define COMMAND "echo"

int	builtin_echo(char **argv)
{
	bool	flag;
	bool	is_option_n;

	if (argv == NULL)
		return (1);
	is_option_n = false;
	while (*argv != NULL && ft_strncmp(*argv, "-n", 3))
	{
		is_option_n = true;
		argv++;
	}
	flag = true;
	while (*argv != NULL && *(argv + 1) != NULL)
	{
		flag &= ft_printf("%s ", *argv) == (ft_strlen(*argv) + 1);
		argv++;
	}
	if (*argv != NULL)
		flag &= ft_printf("%s", *argv) == (ft_strlen(*argv));
	if (!is_option_n)
		flag &= ft_printf("\n") == 1;
	if (!flag)
		return (print_error(COMMAND, NULL, PRINTFERR, 1));
	return (0);
}
