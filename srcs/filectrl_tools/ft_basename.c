/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 10:21:53 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/04 10:28:50 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - NULL
#include <stddef.h>

#include "ft_string/ft_string.h"

#include "_filectrl_tools.h"

char	*ft_basename(const char *path)
{
	char	*pos;

	if (path == NULL)
		return (ft_strdup(""));
	pos = ft_strrchr(path, '/');
	if (pos == NULL)
		return (ft_strdup(""));
	return (ft_strdup(path + 1));
}
