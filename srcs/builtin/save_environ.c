/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:09:14 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/22 02:09:14 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdbool.h>

char	***get_saved_environs(void)
{
	static char	**save_env = NULL;

	return (&save_env);
}

char	**get_environs(void)
{
	return (*get_saved_environs());
}

void	dispose_environs(void)
{
	free_all(*get_saved_environs());
	*get_saved_environs() = NULL;
}

bool	init_environs(char **src)
{
	char	**tmp;
	char	**dst;

	if (src == NULL || get_environs() != NULL)
		return (false);
	dst = (char **)malloc((get_strslen(src) + 1) * sizeof (char *));
	if (dst == NULL)
		return (false);
	tmp = dst;
	while (*src != NULL)
	{
		*tmp = ft_strdup(*src);
		if (*tmp == NULL)
		{
			free_all(dst);
			return (false);
		}
		tmp++;
		src++;
	}
	*tmp = NULL;
	*get_saved_environs() = dst;
	return (true);
}
