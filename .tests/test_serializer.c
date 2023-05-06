/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_serializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:16:35 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/06 13:05:46 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serializer.h"

#define STR(S) (#S)

static const char	*_cmdelmtyp_to_string(t_cmd_elem_type type)
{
	if (type == CMDTYP_NORMAL)
		return (STR(CMDTYP_NORMAL));
	else if (type == CMDTYP_VARIABLE)
		return (STR(CMDTYP_VARIABLE));
	else if (type == CMDTYP_QUOTE_VAR)
		return (STR(CMDTYP_QUOTE_VAR));
	else if (type == CMDTYP_RED_IN)
		return (STR(CMDTYP_RED_IN));
	else if (type == CMDTYP_RED_HEREDOC)
		return (STR(CMDTYP_RED_HEREDOC));
	else if (type == CMDTYP_RED_OUT)
		return (STR(CMDTYP_RED_OUT));
	else if (type == CMDTYP_RED_APPEND)
		return (STR(CMDTYP_RED_APPEND));
	else if (type == CMDTYP_PIPE)
		return (STR(CMDTYP_PIPE));
	return (NULL);
}

static void	print_elem(size_t i, const t_cmd_elem *elem)
{
	char	*buf;

	buf = calloc(elem->len + 1, 1);
	if (buf == NULL)
	{
		perror("ERR");
		exit(1);
	}
	memcpy(buf, elem->elem_top, elem->len);
	printf("\telem[%zu]: %16s '%s'(%zu) -> spc:%d\n",
		i,
		_cmdelmtyp_to_string(elem->type),
		buf,
		elem->len,
		elem->nospace);
	free(buf);
}

static void	print_elemarr(const t_cmdelmarr *elemarr)
{
	size_t		i;

	i = 0;
	while (i < elemarr->len)
	{
		print_elem(i, (t_cmd_elem *)vect_at(elemarr, i));
		i++;
	}
}

static void	print_cmdarr(const t_cmdarr *cmdarr)
{
	size_t		i;

	i = 0;
	while (i < cmdarr->len)
	{
		printf("cmd[%zu] ~~~~~~~~~~~~~~~~~~\n", i);
		print_elemarr((t_cmdelmarr *)vect_at(cmdarr, i++));
	}
}

int	main(int argc, const char *argv[])
{
	t_cmdarr	arr;
	int			i;

	if (argc == 1)
	{
		fputs("Please set argument", stderr);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		printf("\nargv[%i]: '%s'\n", i, argv[i]);
		arr = serialize(argv[i]);
		print_cmdarr(&arr);
		dispose_t_cmdarr(&arr);
		i++;
	}
	puts("");
	return (0);
}

# define DEBUG_LEAKS_CMD_LEN (32)

__attribute__((destructor))
static void	destructor(void) {
	char	cmd[DEBUG_LEAKS_CMD_LEN];

	if (getenv("DEBUG") == NULL)
		return ;
	snprintf(cmd, DEBUG_LEAKS_CMD_LEN, "leaks %d", getpid());
	system(cmd);
}
