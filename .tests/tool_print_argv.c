/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_print_argv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 17:18:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 17:19:31 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(int argc, const char *argv[])
{
	int	i;

	i = 0;
	while (i < argc)
	{
		printf("argv[%d]: `%s`\n", i, argv[i]);
		i++;
	}
	return (0);
}
