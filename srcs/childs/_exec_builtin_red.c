/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _exec_builtin_red.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitsuki <kitsuki@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 21:21:17 by kfujita           #+#    #+#             */
/*   Updated: 2023/06/03 22:15:52 by kitsuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - STDIN_FILENO
// - STDOUT_FILENO
#include <unistd.h>

#include "builtin.h"
#include "childs.h"
#include "error_utils.h"
#include "_redirect.h"

static bool	_dup2_and_close(const t_ch_proc_info *info)
{
	int	status_in;
	int	status_out;

	status_in = 0;
	status_out = 0;
	if (info->fd_to_this != STDIN_FILENO)
		status_in = dup2(info->fd_to_this, STDIN_FILENO);
	if (status_in < 0)
		strerr_ret_false("dup2 IN");
	if (info->fd_to_this != STDIN_FILENO)
		close(info->fd_to_this);
	if (0 <= status_in && info->fd_from_this != STDOUT_FILENO)
		status_out = dup2(info->fd_from_this, STDOUT_FILENO);
	if (status_out < 0)
		strerr_ret_false("dup2 OUT");
	if (info->fd_from_this != STDOUT_FILENO)
		close(info->fd_from_this);
	return (0 <= status_in && 0 <= status_out);
}

// !! ERR_PRINTED
// -> <inherit> _proc_redirect
// -> <inherit> exec_builtin
int	_exec_builtin_red(
	t_ch_proc_info *info,
	int *cpstat
)
{
	int		status;
	bool	tf;

	if (!is_builtin(info->argv))
		return (0);
	if (!_proc_redirect(info))
	{
		*cpstat = 0x100;
		return (1);
	}
	tf = _dup2_and_close(info);
	status = 1;
	if (tf)
		status = exec_builtin(info->argv, cpstat);
	if (info->fd_to_this != STDIN_FILENO
		&& dup2(info->fd_stdin_save, STDIN_FILENO) < 0)
		tf = strerr_ret_false("dup2 revert IN");
	if (info->fd_from_this != STDOUT_FILENO
		&& dup2(info->fd_stdout_save, STDOUT_FILENO) < 0)
		tf = strerr_ret_false("dup2 revert OUT");
	if (!tf && 0 < status)
		*cpstat = 1;
	*cpstat = (*cpstat & 0xFF) << 8;
	if (status < 0)
		*cpstat += (1 << 16);
	return (status);
}
