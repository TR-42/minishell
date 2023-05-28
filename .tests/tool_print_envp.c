/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_print_envp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 14:58:37 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 15:11:53 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, const char *argv[], const char *envp[])
{
	(void)argc;
	(void)argv;
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (0);
}