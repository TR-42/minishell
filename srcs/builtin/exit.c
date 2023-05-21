/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:36:33 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/21 14:36:33 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_is/ft_is.h"
#include "ft_string/ft_string.h"
#include <stdlib.h>

int	builtin_exit(char *arg)
{
	int	status;

	if (arg == NULL)
		status = errno;
	else if (!is_all_digits(arg))
		status = 1;
	else
		status = ft_atoi(arg);
	set_environs(NULL);
	exit(status);
	return (status);
}

static bool	is_all_digits(char *src)
{
	if (src == NULL)
		return (false);
	while (*src != '\0')
	{
		if (!ft_isdigit(*src))
			return (false);
		src++;
	}
	return (true);
}
