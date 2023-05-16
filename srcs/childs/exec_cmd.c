/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:05:51 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/15 08:49:13 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - bool
#include <stdbool.h>

// - close
#include <unistd.h>

// - exit
#include <stdlib.h>

// - dup2
// - execve
#include <unistd.h>

#include "_build_cmd.h"
#include "_childs.h"
#include "_filectrl_tools.h"

static bool	_proc_redirect(t_ch_proc_info *info)
{
	(void)info;
	return (true);
}

static void	dup2_and_close(int fd_dup_from, int fd_dup_to)
{
	if (fd_dup_from == fd_dup_to)
		return ;
	dup2(fd_dup_from, fd_dup_to);
	close(fd_dup_from);
}

// TODO: エラー時にFDを閉じる?
noreturn void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	char	**envp;
	char	**argv;
	char	*exec_path;
	bool	ret;

	if (!_proc_redirect(info_arr + index))
		exit(1);
	exec_path = NULL;
	envp = info_arr[index].envp;
	argv = build_cmd(info_arr[index].cmd, info_arr[index].envp);
	ret = chk_and_get_fpath(argv[0], info_arr[index].path_arr, &exec_path);
	if (ret != true)
	{
		dispose_proc_info_arr(info_arr);
		exit(1);
	}
	dup2_and_close(info_arr[index].fd_to_this, STDIN_FILENO);
	dup2_and_close(info_arr[index].fd_from_this, STDOUT_FILENO);
	dispose_proc_info_arr(info_arr);
	execve(exec_path, argv, envp);
	free(argv);
	exit(1);
}
