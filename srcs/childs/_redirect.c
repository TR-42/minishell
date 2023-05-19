/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _redirect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 01:03:57 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 20:38:29 by kfujita          ###   ########.fr       */
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

// TODO: heredocのサポート
static bool	_open_set_close_fd(t_ch_proc_info *info, t_cmd_elem_type type,
	const char *fname)
{
	int	fd;

	if (type == CMDTYP_RED_IN)
		fd = open(fname, O_RDONLY | O_CLOEXEC);
	else if (type == CMDTYP_RED_OUT)
		fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(fname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_dprintf(STDERR_FILENO, "minishell: %s: %s\n",
				fname, strerror(errno)) * 0);
	if (type == CMDTYP_RED_IN)
	{
		if (info->fd_to_this != STDIN_FILENO)
			close(info->fd_to_this);
		info->fd_to_this = fd;
	}
	else
	{
		if (info->fd_from_this != STDIN_FILENO)
			close(info->fd_from_this);
		info->fd_from_this = fd;
	}
	return (true);
}

// TODO: heredocのサポート
bool	_proc_redirect(t_ch_proc_info *info)
{
	size_t		i;
	char		*fname;
	int			type;

	i = 0;
	while (i < info->cmd->len)
	{
		type = ((t_cmd_elem *)(info->cmd->p))[i++].type;
		if (is_cetyp_redirect((t_cmd_elem_type)type)
			&& type != CMDTYP_RED_HEREDOC)
		{
			fname = _get_argv_one(info->cmd, &i, info->envp);
			if (fname == NULL)
				return (_perror_ret_false("minishell/_proc_redirect"));
			type = _open_set_close_fd(info, (t_cmd_elem_type)type, fname);
			free(fname);
			if (!type)
				return (false);
		}
	}
	return (true);
}
