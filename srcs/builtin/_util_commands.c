/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _util_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:05:53 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/22 02:05:53 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>

size_t	get_strslen(char **src)
{
	size_t	count;

	if (src == NULL)
		return (0);
	count = 0;
	while (src[count] != NULL)
		count++;
	return (count);
}

bool	free_all(char ***dst)
{
	char	**tmp;

	if (dst == NULL || *dst == NULL)
		return (false);
	tmp = *dst;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp ++;
	}
	free(*dst);
	*dst = NULL;
	return (false);
}
