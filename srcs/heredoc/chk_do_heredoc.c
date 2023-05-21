/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chk_do_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 19:57:31 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 13:50:21 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - perror
#include <stdio.h>

// - free
#include <stdlib.h>

// - STDIN_FILENO
#include <unistd.h>

#include "ft_put/ft_put.h"
#include "ft_string/ft_string.h"
#include "gnl/get_next_line.h"

#include "../childs/_build_cmd.h"
#include "heredoc.h"

#define PROMPT_STR "> "

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

static bool	_read_write(const char *term, int fd)
{
	t_gnl_state	state;
	char		*gnl_result;

	state = gen_gnl_state(STDIN_FILENO, 256);
	if (state.buf == NULL)
		return (false);
	gnl_result = NULL;
	while (true)
	{
		write(STDOUT_FILENO, PROMPT_STR, sizeof(PROMPT_STR) - 1);
		gnl_result = get_next_line(&state);
		if (gnl_result == NULL || is_same_line(term, gnl_result))
			break ;
		ft_putstr_fd(state.buf, fd);
		free(gnl_result);
	}
	free(gnl_result);
	dispose_gnl_state(&state);
	return (true);
}

// TODO: readlineを使って書き直す
static bool	_do_heredoc(const t_cmdelmarr *elems, size_t *i, int fd)
{
	char	*term;
	bool	result;

	term = _get_argv_one(elems, i, NULL);
	if (term == NULL)
		return (false);
	result = _read_write(term, fd);
	free(term);
	return (result);
}

static bool	_chk_do_heredoc_elemarr(t_cmdelmarr *elemarr, char *const *envp)
{
	int			fd;
	t_cmd_elem	*elems;
	size_t		i_elem;
	bool		result;

	elems = (t_cmd_elem *)(elemarr->p);
	i_elem = 0;
	result = true;
	while (result && i_elem < elemarr->len)
	{
		if (elems[i_elem++].type == CMDTYP_RED_HEREDOC)
		{
			elems[i_elem - 1].type = CMDTYP_RED_HEREDOC_SAVED;
			fd = create_tmpfile(envp, (char **)&(elems[i_elem - 1].elem_top));
			if (fd < 0)
				return (false);
			result = _do_heredoc(elemarr, &i_elem, fd);
			close(fd);
		}
	}
	return (result);
}

bool	chk_do_heredoc(t_cmdarr *cmdarr, char *const *envp)
{
	size_t		i_cmd;
	t_cmdelmarr	*cmds;

	i_cmd = 0;
	cmds = (t_cmdelmarr *)(cmdarr->p);
	while (i_cmd < cmdarr->len)
	{
		if (!_chk_do_heredoc_elemarr(cmds + i_cmd, envp))
			return (false);
		i_cmd += 1;
	}
	return (true);
}
