/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 17:16:51 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/16 17:16:51 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "ft_mem/ft_mem.h"
#include <sys/param.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#ifndef PATH_MAX
# define PATH_MAX MAXPATHLEN
#endif

bool	builtin_pwd(void)
{
	char	path[PATH_MAX + 1];

	ft_bzero(path, PATH_MAX + 1);
	if (getcwd(path, PATH_MAX) != NULL)
	{
		ft_printf("%s\n", path);
		return (true);
	}
	return (false);
}
