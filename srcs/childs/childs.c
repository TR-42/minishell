/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:56:28 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/24 09:27:46 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - noreturn
#include <stdnoreturn.h>

// - perror
#include <stdio.h>

// - exit
#include <stdlib.h>

#include "error_utils.h"

#include "_childs.h"

// !! ERR_PRINTED
// -> (root) for pipe function
static bool	create_pipe(t_ch_proc_info *info_arr, size_t index)
{
	int		pipefd[2];

	if (get_cmdterm(info_arr[index].cmd) != CMDTYP_PIPE)
		return (true);
	if (pipe(pipefd) < 0)
	{
		perr_ret_false("minishell/pipe");
		if (info_arr[index].fd_to_this != STDIN_FILENO)
			close(info_arr[index].fd_to_this);
		return (false);
	}
	info_arr[index].fd_from_this = pipefd[PIPEFD_FROM_THIS];
	info_arr[index + 1].fd_to_this = pipefd[PIPEFD_FROM_PREV];
	return (true);
}

// !! ERR_PRINTED
// -> <inherit> create_pipe
// -> (root) for fork function
bool	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index,
	size_t count, int exit_stat)
{
	int	_errno;

	if (!create_pipe(info_arr, index))
		return (false);
	if (info_arr[index].argv != NULL)
		info_arr[index].pid = fork();
	_errno = errno;
	if (info_arr[index].argv != NULL && info_arr[index].pid == PID_FORKED)
		exec_command(info_arr, index, exit_stat);
	if (info_arr[index].fd_from_this != STDOUT_FILENO)
		close(info_arr[index].fd_from_this);
	if (info_arr[index].fd_to_this != STDIN_FILENO)
		close(info_arr[index].fd_to_this);
	if (info_arr[index].pid < 0)
	{
		if ((index + 1) != count
			&& info_arr[index + 1].fd_to_this != STDIN_FILENO)
			close(info_arr[index].fd_to_this);
		return (strerr_errno_ret_false("(fork)", _errno));
	}
	return (true);
}
