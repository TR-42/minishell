/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:59 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/20 20:53:59 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>

#define ERROR_MESSAGE "unset: %s: invalid parameter name\n"

bool	builtin_unset(char **args)
{
	bool	flag;

	flag = false;
	if (args == NULL)
		reutrn (false);
	while (*args != NULL)
	{
		if (!remove_environ(*args) && !flag)
		{
			flag = true;
			ft_dprintf(STDERR_FILENO, ERROR_MESSAGE, *args);
		}
		args ++;
	}
}
