/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:05:51 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 01:23:34 by kfujita          ###   ########.fr       */
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
		info->fd_stdin_save = dup(STDIN_FILENO);
		dup2(info->fd_to_this, STDIN_FILENO);
		close(info->fd_to_this);
		info->fd_to_this = -1;
	}
	if (info->fd_from_this != STDOUT_FILENO)
	{
		info->fd_stdout_save = dup(STDOUT_FILENO);
		dup2(info->fd_from_this, STDOUT_FILENO);
		close(info->fd_from_this);
		info->fd_from_this = -1;
	}
}

static void	_revert_stdio(const t_ch_proc_info *info)
{
	if (info->fd_stdin_save != 0)
	{
		dup2(info->fd_stdin_save, STDIN_FILENO);
		close(info->fd_stdin_save);
	}
	if (info->fd_stdout_save != 0)
	{
		dup2(info->fd_stdout_save, STDOUT_FILENO);
		close(info->fd_stdout_save);
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
		dispose_proc_info_arr(info_arr);
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
	_revert_stdio(&info);
	free_2darr((void ***)&argv);
	exit(1);
}
