/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:03:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/22 19:52:12 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - open
#include <fcntl.h>

// - perror
#include <stdio.h>

// - free
#include <stdlib.h>

// - strerror
#include <string.h>

// - close
// - STDERR_FILENO
// - STDIN_FILENO
// - STDOUT_FILENO
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "error_utils.h"

#include "_build_cmd.h"
#include "_redirect.h"

// !! ERR_PRINTED
// -> (root) for open function
// -> (root) for invalid elemtype (実装ミスでない限り到達しない…はず)
__attribute__((nonnull))
static bool	_open_set_close_fd(t_ch_proc_info *info, t_cmd_elem_type type,
	const char *fname)
{
	int	fd;

	if (type == CMDTYP_RED_IN || type == CMDTYP_RED_HEREDOC_SAVED)
		fd = open(fname, O_RDONLY | O_CLOEXEC);
	else if (type == CMDTYP_RED_OUT)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == CMDTYP_RED_APPEND)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (ft_dprintf(STDERR_FILENO,
				"minishell: redirect: unknown cmdtype: %d\n", type) * 0);
	if (fd < 0)
		return (strerr_ret_false(fname));
	if (type == CMDTYP_RED_IN || type == CMDTYP_RED_HEREDOC_SAVED)
	{
		if (info->fd_to_this != STDIN_FILENO)
			close(info->fd_to_this);
		info->fd_to_this = fd;
		return (true);
	}
	if (info->fd_from_this != STDIN_FILENO)
		close(info->fd_from_this);
	info->fd_from_this = fd;
	return (true);
}

// !! ERR_PRINTED
// -> (root) for saved file name (バリデーション済みのため到達しない…はず)
// -> <inherit> _get_argv_one
__attribute__((nonnull))
static char	*_get_red_fname(const t_ch_proc_info *info, size_t *i,
	t_cmd_elem_type type)
{
	char	*tmp;

	if (type == CMDTYP_RED_HEREDOC_SAVED)
	{
		tmp = ((char *)(((t_cmd_elem *)info->cmd->p)[*i - 1].elem_top));
		if (tmp == NULL)
			errstr_ret_false("_get_red_fname()",
				"file path for heredoc cache was NULL");
		return (tmp);
	}
	else
		return (_get_argv_one(info->cmd, i, info->envp));
}

// !! ERR_PRINTED
// -> <inherit> for _get_red_fname
// -> <inherit> _open_set_close_fd
__attribute__((nonnull))
bool	_proc_redirect(t_ch_proc_info *info)
{
	size_t			i;
	char			*fname;
	t_cmd_elem_type	type;
	bool			result;

	i = 0;
	while (i < info->cmd->len)
	{
		type = ((t_cmd_elem *)(info->cmd->p))[i++].type;
		if (!is_cetyp_redirect(type))
			continue ;
		fname = _get_red_fname(info, &i, type);
		if (fname == NULL)
			return (false);
		result = _open_set_close_fd(info, type, fname);
		free(fname);
		if (type == CMDTYP_RED_HEREDOC_SAVED)
			((t_cmd_elem *)info->cmd->p)[i - 1].elem_top = NULL;
		if (!result)
			return (false);
	}
	return (true);
}
