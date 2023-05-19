/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:05:51 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 22:01:26 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - errno
#include <errno.h>

// - bool
#include <stdbool.h>

// - close
#include <unistd.h>

// - exit
#include <stdlib.h>

// - strerror
#include <string.h>

// - dup2
// - execve
#include <unistd.h>

#include "ft_printf/ft_printf.h"

#include "_build_cmd.h"
#include "_childs.h"
#include "_filectrl_tools.h"
#include "_redirect.h"

// TODO: エラー処理
static void	dup2_and_close(t_ch_proc_info *info)
{
	if (info->fd_to_this != STDIN_FILENO)
	{
		dup2(info->fd_to_this, STDIN_FILENO);
		close(info->fd_to_this);
		info->fd_to_this = -1;
	}
	else
	{
		close(info->fd_stdin_save);
		info->fd_stdin_save = -1;
	}
	if (info->fd_from_this != STDOUT_FILENO)
	{
		dup2(info->fd_from_this, STDOUT_FILENO);
		close(info->fd_from_this);
		info->fd_from_this = -1;
	}
	else
	{
		close(info->fd_stdout_save);
		info->fd_stdout_save = -1;
	}
}

static void	free_2darr(void ***argv)
{
	size_t	i;

	if (argv == NULL || *argv == NULL)
		return ;
	i = 0;
	while ((*argv)[i] != NULL)
		free((*argv)[i++]);
	free(*argv);
	*argv = NULL;
}

static void	_revert_stdio_dispose_arr(
	const t_ch_proc_info *info,
	t_ch_proc_info *info_arr,
	char ***argv)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	if (0 < info->fd_stdin_save)
	{
		dup2(info->fd_stdin_save, STDIN_FILENO);
		close(info->fd_stdin_save);
	}
	if (0 < info->fd_stdout_save)
	{
		dup2(info->fd_stdout_save, STDOUT_FILENO);
		close(info->fd_stdout_save);
	}
	if (0 <= info->fd_to_this && info->fd_to_this != STDIN_FILENO)
		close(info->fd_to_this);
	if (0 <= info->fd_from_this && info->fd_from_this != STDOUT_FILENO)
		close(info->fd_from_this);
	if (info_arr != NULL)
		dispose_proc_info_arr(info_arr);
	if (argv != NULL)
		free_2darr((void ***)argv);
}

// TODO: エラー時にFDを閉じる?
noreturn void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	t_ch_proc_info	info;
	char			**argv;
	char			*exec_path;
	bool			ret;

	info = info_arr[index];
	if (!_proc_redirect(&info))
	{
		_revert_stdio_dispose_arr(&info, info_arr, NULL);
		exit(1);
	}
	exec_path = NULL;
	argv = build_cmd(info.cmd, info.envp);
	ret = chk_and_get_fpath(argv[0], info.path_arr, &exec_path);
	if (ret == true)
		dup2_and_close(&info);
	dispose_proc_info_arr(info_arr);
	if (ret == true)
		execve(exec_path, argv, info.envp);
	if (ret == true)
		ft_dprintf(STDERR_FILENO,
			"minishell: %s: %s\n", argv[0], strerror(errno));
	_revert_stdio_dispose_arr(&info, NULL, &argv);
	exit(1);
}
