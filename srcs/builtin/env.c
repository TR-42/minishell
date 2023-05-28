/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 20:53:24 by kitsuki           #+#    #+#             */
/*   Updated: 2023/05/20 20:53:24 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_environ.h"
#include "ft_printf/ft_printf.h"

int	builtin_env(void)
{
	char	**envs;

	envs = *get_saved_environs();
	if (envs == NULL)
		return ;
	while (*envs != NULL)
	{
		ft_printf("%s\n", *envs);
		envs++;
	}
}
