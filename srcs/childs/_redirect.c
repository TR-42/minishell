/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:03:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/21 14:14:21 by kfujita          ###   ########.fr       */
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

#include "_build_cmd.h"
#include "_redirect.h"

static bool	_perror_ret_false(const char *str)
{
	perror(str);
	return (false);
}

static bool	_open_set_close_fd(t_ch_proc_info *info, t_cmd_elem_type type,
	const char *fname)
{
	int	fd;

	if (type == CMDTYP_RED_APPEND || type == CMDTYP_RED_HEREDOC_SAVED)
		fd = open(fname, O_RDONLY | O_CLOEXEC);
	else if (type == CMDTYP_RED_OUT)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == CMDTYP_RED_APPEND)
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (ft_dprintf(STDERR_FILENO,
				"minishell: redirect: unknown cmdtype: %d\n", type) * 0);
	if (fd < 0)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
				fname, strerror(errno)) * 0);
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

static char	*_get_red_fname(const t_ch_proc_info *info, size_t *i,
	t_cmd_elem_type type)
{
	if (type == CMDTYP_RED_HEREDOC_SAVED)
		return ((char *)(((t_cmd_elem *)info->cmd->p)[*i - 1].elem_top));
	else
		return (_get_argv_one(info->cmd, i, info->envp));
}

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
			return (_perror_ret_false("minishell/_proc_redirect"));
		result = _open_set_close_fd(info, type, fname);
		free(fname);
		if (type == CMDTYP_RED_HEREDOC_SAVED)
			((t_cmd_elem *)info->cmd->p)[i - 1].elem_top = NULL;
		if (!result)
			return (false);
	}
	return (true);
}
