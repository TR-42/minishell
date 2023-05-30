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

#include "error_utils.h"
#include "_build_cmd.h"
#include "_childs.h"
#include "_filectrl_tools.h"
#include "_redirect.h"
#include "utils.h"

// !! PRINT_ERROR
// -> (root) for dup2 function
// (close関数は失敗しない前提。失敗したとしても、リトライしようがないため無視する)
__attribute__((nonnull))
static bool	_dup2_and_set_inval(int *p_fd, int target_fd, const char *err_msg)
{
	bool	is_success;

	is_success = false;
	if (*p_fd != target_fd)
		is_success = 0 <= dup2(*p_fd, target_fd);
	if (!is_success)
		strerr_ret_false(err_msg);
	close(*p_fd);
	*p_fd = -1;
	return (is_success);
}

// !! PRINT_ERROR
// -> <inherit> _dup2_and_set_inval
static bool	dup2_and_close(t_ch_proc_info *info)
{
	int		*p_fd;
	bool	is_success;

	if (info->fd_to_this != STDIN_FILENO)
		p_fd = &(info->fd_to_this);
	else
		p_fd = &(info->fd_stdin_save);
	is_success = _dup2_and_set_inval(p_fd, STDIN_FILENO, "dup2 IN");
	if (info->fd_from_this != STDOUT_FILENO)
		p_fd = &(info->fd_from_this);
	else
		p_fd = &(info->fd_stdout_save);
	if (!is_success)
		return (close(*p_fd) * 0);
	return (!_dup2_and_set_inval(p_fd, STDOUT_FILENO, "dup2 OUT"));
}

// !! NO_ERROR
// (dup2でエラーの可能性はあるけど、この関数はエラールートで実行されるため、改めてエラーを吐くことはしない。)
// (そもそも、dup2でエラーが起きる可能性自体低いし。)
static noreturn void	_revert_stdio_dispose_arr(
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
	exit(1);
}

// !! ERR_PRINTED
// -> <inherit> _proc_redirect
// -> <inherit> chk_and_get_fpath
// -> (root) for execve
__attribute__((nonnull))
noreturn void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	t_ch_proc_info	info;
	char			*exec_path;
	bool			ret;

	info = info_arr[index];
	if (!_proc_redirect(&info))
		_revert_stdio_dispose_arr(&info, info_arr, &(info.argv));
	exec_path = NULL;
	ret = chk_and_get_fpath(info.argv[0], info.path_arr, &exec_path);
	if (ret == true)
		dup2_and_close(&info);
	dispose_proc_info_arr(info_arr);
	if (ret == true)
		execve(exec_path, info.argv, info.envp);
	if (ret == true)
		strerr_ret_false(info.argv[0]);
	_revert_stdio_dispose_arr(&info, NULL, &(info.argv));
	exit(1);
}
