/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _util_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 02:05:53 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/31 15:59:48 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "ft_printf/ft_printf.h"

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

void	free_all(char **dst)
{
	char	**tmp;

	if (dst == NULL)
		return ;
	tmp = dst;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp ++;
	}
	free(dst);
}

int	print_error(char *command, char *name, char *message, int err)
{
	ft_dprintf(STDERR_FILENO, "minishell: ");
	if (command != NULL)
		ft_dprintf(STDERR_FILENO, "%s: ", command);
	if (name != NULL)
		ft_dprintf(STDERR_FILENO, "`%s': ", name);
	if (message == NULL)
		message = strerror(err);
	ft_dprintf(STDERR_FILENO, "%s\n", message);
	return (err);
}
