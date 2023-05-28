/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:24 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/28 20:05:34 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_printf/ft_printf.h"
#include "ft_string/ft_string.h"
#include "_util_commands.h"
#include <unistd.h>

#define COMMAND "env"

int	builtin_env(char **argv)
{
	char	**envs;

	if (*(++argv) != NULL)
		return (print_error(COMMAND, NULL, ARGERR, 1));
	envs = *get_saved_environs();
	if (envs == NULL)
		return (0);
	while (*envs != NULL)
	{
		if (ft_strchr(*envs, '=') != NULL)
		{
			if (ft_putstr_fd_with_err(*envs, STDOUT_FILENO) == 0
				|| ft_putstr_fd_with_err("\n", STDOUT_FILENO) == 0)
				return (print_error(COMMAND, NULL, PRINTFERR, 1));
		}
		envs++;
	}
	return (0);
}
