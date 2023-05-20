/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_serializer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 23:16:35 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/17 09:16:21 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "serializer.h"
#include "validator.h"

#include "../srcs/childs/_build_cmd.h"

#define COLOR_DEFAULT "\033[0;0m"

#define COLOR_RED "\033[0;31m"
#define COLOR_GREEN "\033[0;32m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_BLUE "\033[0;34m"
#define COLOR_PURPLE "\033[0;35m"
#define COLOR_CYAN "\033[0;36m"

#define COLOR_BOLD_GRAY "\033[1;30m"
#define COLOR_BOLD_RED "\033[1;31m"
#define COLOR_BOLD_GREEN "\033[1;32m"
#define COLOR_BOLD_YELLOW "\033[1;33m"
#define COLOR_BOLD_BLUE "\033[1;34m"
#define COLOR_BOLD_PURPLE "\033[1;35m"
#define COLOR_BOLD_CYAN "\033[1;36m"

#define STR(S) #S

static const char	*_cmdelmtyp_to_string(t_cmd_elem_type type)
{
	if (type == CMDTYP_NORMAL)
		return (COLOR_BOLD_GREEN STR(CMDTYP_NORMAL) COLOR_DEFAULT);
	else if (type == CMDTYP_VARIABLE)
		return (COLOR_BOLD_PURPLE STR(CMDTYP_VARIABLE) COLOR_DEFAULT);
	else if (type == CMDTYP_QUOTE_VAR)
		return (COLOR_BOLD_PURPLE STR(CMDTYP_QUOTE_VAR) COLOR_DEFAULT);
	else if (type == CMDTYP_RED_IN)
		return (COLOR_BOLD_BLUE STR(CMDTYP_RED_IN) COLOR_DEFAULT);
	else if (type == CMDTYP_RED_HEREDOC)
		return (COLOR_BOLD_BLUE STR(CMDTYP_RED_HEREDOC) COLOR_DEFAULT);
	else if (type == CMDTYP_RED_OUT)
		return (COLOR_BOLD_CYAN STR(CMDTYP_RED_OUT) COLOR_DEFAULT);
	else if (type == CMDTYP_RED_APPEND)
		return (COLOR_BOLD_CYAN STR(CMDTYP_RED_APPEND) COLOR_DEFAULT);
	else if (type == CMDTYP_PIPE)
		return (COLOR_BOLD_YELLOW STR(CMDTYP_PIPE) COLOR_DEFAULT);
	return (NULL);
}

static const char	*_cmd_inval_typ_to_string(t_cmd_inval_typ type)
{
	if (type == CMD_INVAL_NO_ERR)
		return (COLOR_GREEN STR(CMD_INVAL_NO_ERR) COLOR_DEFAULT);
	else if (type == CMD_INVAL_NOCMD)
		return (COLOR_BOLD_RED STR(CMD_INVAL_NOCMD) COLOR_DEFAULT);
	else if (type == CMD_INVAL_PIPE_NOPAIR)
		return (COLOR_PURPLE STR(CMD_INVAL_PIPE_NOPAIR) COLOR_DEFAULT);
	else if (type == CMD_INVAL_REDIRECT_NOARG)
		return (COLOR_RED STR(CMD_INVAL_REDIRECT_NOARG) COLOR_DEFAULT);
	return (NULL);
}

static void	print_elem(size_t i, const char *str, const t_cmd_elem *elem)
{
	char	*buf;
	long	offset;

	buf = calloc(elem->len + 1, 1);
	if (buf == NULL)
	{
		perror("ERR");
		exit(1);
	}
	offset = elem->elem_top - str;
	memcpy(buf, elem->elem_top, elem->len);
	printf("\telem[%2zu]:%32s '%s'(%ld .. %zu) -> spc:%d\n",
		i,
		_cmdelmtyp_to_string(elem->type),
		buf,
		offset,
		elem->len,
		elem->nospace);
	free(buf);
}

static void	print_elemarr(const char *str, const t_cmdelmarr *elemarr, bool is_last)
{
	size_t		i;

	i = 0;
	while (i < elemarr->len)
	{
		print_elem(i, str, (t_cmd_elem *)vect_at(elemarr, i));
		i++;
	}
	printf("\t\t(AGRC: %d / isValid?: %s)\n",
	_get_argc(elemarr),
	_cmd_inval_typ_to_string(is_valid_cmd(elemarr, is_last)));
}

static void	print_cmdarr(const char *str, const t_cmdarr *cmdarr)
{
	size_t			i;
	t_cmd_i_inval	ret;

	i = 0;
	while (i < cmdarr->len)
	{
		ret = is_valid_input(cmdarr);
		printf("cmd[%zu] ~~~~~~~~~~~~~~~~~~ (isValid?: %s at %zu)\n", i, _cmd_inval_typ_to_string(ret.type), ret.index);
		print_elemarr(
			str,
			(t_cmdelmarr *)vect_at(cmdarr, i),
			(i + 1) == cmdarr->len);
		i++;
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
		print_cmdarr(argv[i], &arr);
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
