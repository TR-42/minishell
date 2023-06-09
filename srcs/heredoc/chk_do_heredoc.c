/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_do_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:57:31 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/28 18:36:24 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - perror
#include <stdio.h>

// - free
#include <stdlib.h>

// - readline etc.
#include <readline/readline.h>

// - STDIN_FILENO
#include <unistd.h>

#include "ft_put/ft_put.h"
#include "ft_string/ft_string.h"

#include "_build_cmd.h"
#include "builtin.h"
#include "error_utils.h"
#include "heredoc.h"
#include "signal_handling.h"

#define PROMPT_STR "> "

// !! NO_ERR
static bool	is_same_line(const char *a, const char *b)
{
	if (a == NULL && b == NULL)
		return (true);
	else if (a == NULL || b == NULL)
		return (false);
	while (true)
	{
		if (*a != *b)
		{
			if ((*a == '\0' && *b == '\n') || (*a == '\n' && *b == '\0'))
				return (true);
			else
				return (false);
		}
		else if (*a == '\0')
			return (true);
		a++;
		b++;
	}
}

// !! NO_ERR (readlineを使用することによりエラーは発生しなくなる)
static bool	_read_write(const char *term, int fd)
{
	char	*gnl_result;

	gnl_result = NULL;
	while (true)
	{
		gnl_result = readline(PROMPT_STR);
		if (gnl_result == NULL || get_is_interrupted()
			|| is_same_line(term, gnl_result))
			break ;
		ft_putendl_fd(gnl_result, fd);
		free(gnl_result);
	}
	free(gnl_result);
	return (!get_is_interrupted());
}

// !! ERR_PRINTED
// -> <inherit> _get_argv_one
static bool	_do_heredoc(const t_cmdelmarr *elems, size_t *i, int fd)
{
	char	*term;
	bool	result;

	term = _get_argv_one(elems, i);
	if (term == NULL)
		return (false);
	result = _read_write(term, fd);
	free(term);
	return (result);
}

// !! ERR_PRINTED
// -> <inherit> create_tmpfile
// -> <inherit> _do_heredoc
static bool	_chk_do_heredoc_elemarr(t_cmdelmarr *elemarr)
{
	int			fd;
	t_cmd_elem	*elems;
	size_t		i_elem;
	bool		result;
	char		**envp;

	elems = (t_cmd_elem *)(elemarr->p);
	i_elem = 0;
	result = true;
	envp = get_environs();
	while (result && i_elem < elemarr->len)
	{
		if (elems[i_elem++].type == CMDTYP_RED_HEREDOC)
		{
			if (envp == NULL)
				return (errstr_ret_false("(heredoc)", "envp was NULL"));
			elems[i_elem - 1].type = CMDTYP_RED_HEREDOC_SAVED;
			fd = create_tmpfile(envp, &(elems[i_elem - 1].p_malloced));
			if (fd < 0)
				return (false);
			result = _do_heredoc(elemarr, &i_elem, fd);
			close(fd);
		}
	}
	return (result);
}

// !! ERR_PRINTED
// -> <inherit> _chk_do_heredoc_elemarr
bool	chk_do_heredoc(t_cmdarr *cmdarr)
{
	size_t		i_cmd;
	t_cmdelmarr	*cmds;

	i_cmd = 0;
	cmds = (t_cmdelmarr *)(cmdarr->p);
	while (i_cmd < cmdarr->len)
	{
		ignore_var_in_delimiter(cmds + i_cmd);
		if (!_chk_do_heredoc_elemarr(cmds + i_cmd))
			return (false);
		i_cmd += 1;
	}
	return (true);
}
