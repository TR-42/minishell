/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:36:10 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/21 14:36:10 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_string/ft_string.h"

bool	builtin_export(char **args)
{
	if (args == NULL)
		return (false);
	while (*args != NULL)
	{
		if (ft_strchr(args, '=') != NULL)
			set_environ(*args);
		args++;
	}
	return (true);
}
