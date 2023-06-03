/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:36:33 by kitsuki           #+#    #+#             */
/*   Updated: 2023/06/03 18:43:17 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "_environ.h"
#include "_util_commands.h"
#include "ft_printf/ft_printf.h"
#include "ft_is/ft_is.h"
#include "ft_string/ft_string.h"

#define COMMAND "exit"

int	builtin_exit(char **argv, int status)
{
	char	*tmp;

	ft_dprintf(STDERR_FILENO, "%s\n", COMMAND);
	if (*(++argv) != NULL)
	{
		status = ft_strtol(*argv, &tmp, 10);
		if (**argv == '\0' || (*tmp != '\0' && ft_strncmp(*argv, "--", 3) != 0)
			|| (*tmp == '\0' && !ft_isdigit(*(tmp - 1))))
			return (print_error(COMMAND, *argv, NOTNUMERR, 255));
		status &= 255;
	}
	return (status);
}
