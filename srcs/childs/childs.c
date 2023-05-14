/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:56:28 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/15 01:13:07 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - noreturn
#include <stdnoreturn.h>

// - perror
#include <stdio.h>

// - exit
#include <stdlib.h>

#include "_childs.h"

noreturn static void	_perr_dispose_exit(const char *str, t_ch_proc_info *arr)
{
	perror(str);
	dispose_proc_info_arr(arr);
	exit(1);
}

// TODO: パイプを含む場合のみパイプを繋ぐようにする
static void	create_pipe(t_ch_proc_info *info_arr, size_t index, size_t count)
{
	int		pipefd[2];

	if ((index + 1) == count)
	{
		info_arr[index].fd_from_this = STDOUT_FILENO;
		return ;
	}
	if (pipe(pipefd) < 0)
		_perr_dispose_exit("create pipe", info_arr);
	info_arr[index].fd_from_this = pipefd[PIPEFD_FROM_THIS];
	info_arr[index + 1].fd_to_this = pipefd[PIPEFD_FROM_PREV];
}

void	pipe_fork_exec(t_ch_proc_info *info_arr, size_t index, size_t count)
{
	create_pipe(info_arr, index, count);
	info_arr[index].pid = fork();
	if (info_arr[index].pid < 0)
		_perr_dispose_exit("fork", info_arr);
	else if (info_arr[index].pid == PID_FORKED)
		exec_command(info_arr, index);
	if (info_arr[index].fd_from_this != STDOUT_FILENO)
		close(info_arr[index].fd_from_this);
	if (info_arr[index].fd_to_this != STDIN_FILENO)
		close(info_arr[index].fd_to_this);
}
