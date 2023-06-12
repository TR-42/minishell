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

static bool	identify_endstr(char *arg, char *end);

int	builtin_exit(char **argv, int status, bool is_parent)
{
	char	*tmp;
	size_t	size;

	if (is_parent)
		ft_dprintf(STDERR_FILENO, "%s\n", COMMAND);
	if (*(argv + 1) != NULL && ft_strncmp(*(argv + 1), "--", 3) == 0)
		argv++;
	size = get_strslen(argv);
	if (*(++argv) != NULL)
	{
		status = ft_strtol(*argv, &tmp, 10);
		if (**argv == '\0' || (*tmp == '\0' && !ft_isdigit(*(tmp - 1)))
			|| (*tmp != '\0' && !identify_endstr(*argv, tmp)))
			return (print_error(COMMAND, *argv, NOTNUMERR, 0x1ff));
		status &= 0xff;
	}
	if (size > 2)
		return (print_error(COMMAND, NULL, MANYARGERR, 1));
	status += 0x100;
	return (status);
}

static bool	identify_endstr(char *arg, char *end)
{
	if (arg == end || !ft_isdigit(*(end - 1)))
		return (false);
	while (((9 <= *end && *end <= 13) || *end == ' ') && *end != '\0')
		end++;
	if (*end != '\0')
		return (false);
	return (true);
}
