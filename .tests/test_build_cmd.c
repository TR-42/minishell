/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_build_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:29:09 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/14 20:52:48 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../srcs/childs/_build_cmd.h"

#include "serializer.h"

static void	_free_argv(char **argv)
{
	size_t	i;

	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

static void	_print_argv(const char **argv)
{
	size_t	i;

	if (argv == NULL)
	{
		puts("\t!!! argv is NULL !!!");
		return ;
	}
	i = 0;
	while (argv[i] != NULL)
	{
		printf("\t[%2zu]: `%s`\n", i, argv[i]);
		i++;
	}
}

static void	print_cmdarr(const t_cmdarr *cmdarr, const char **envp)
{
	char		**v;
	size_t		i;
	t_cmdelmarr	*elemarr;

	i = 0;
	while (i < cmdarr->len)
	{
		printf("  cmd[%zu] ~~~~~~~~~~~~~~~~~~\n", i);
		elemarr = (t_cmdelmarr *)vect_at(cmdarr, i++);
		v = build_cmd(elemarr, envp);
		_print_argv((const char **)v);
		_free_argv(v);
	}
}


int	main(int argc, char **argv, const char **envp)
{
	t_cmdarr	arr;
	size_t		i;

	i = 0;
	while (++i < (size_t)argc)
	{
		printf("\nargv[%zu]: '%s'\n", i, argv[i]);
		arr = serialize(argv[i]);
		print_cmdarr(&arr, envp);
		dispose_t_cmdarr(&arr);
	}
	return (0);
}

#define DEBUG_LEAKS_CMD_LEN (32)

__attribute__((destructor))
static void	destructor(void) {
	char	cmd[DEBUG_LEAKS_CMD_LEN];

	if (getenv("DEBUG") == NULL)
		return ;
	snprintf(cmd, DEBUG_LEAKS_CMD_LEN, "leaks %d", getpid());
	system(cmd);
}
