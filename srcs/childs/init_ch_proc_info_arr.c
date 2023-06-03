/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ch_proc_info_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:43:45 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/19 22:01:56 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>

// - malloc
#include <stdlib.h>

// - dup
#include <unistd.h>

#include "childs.h"
#include "error_utils.h"
#include "_env_util.h"

// !! NO_ERR
__attribute__((nonnull))
static t_cprocinf	_init_ch_proc_info(t_cmdarr *cmdarr, size_t i)
{
	t_cprocinf	info;

	info = (t_cprocinf){0};
	info.cmdarr = cmdarr;
	info.cmd = (t_cmdelmarr *)vect_at(cmdarr, i);
	info.fd_to_this = STDIN_FILENO;
	info.fd_from_this = STDOUT_FILENO;
	if (i == 0)
	{
		info.fd_stdin_save = dup(STDIN_FILENO);
		info.fd_stdout_save = dup(STDOUT_FILENO);
	}
	return (info);
}

// !! NO_ERROR
static void	*_err_free_retnull(void *p, const char *str)
{
	strerr_ret_false(str);
	if (p != NULL)
		free(p);
	return (NULL);
}

// !! ERR_PRINTED
// -> (root) for malloc
// -> (root) for get_path_in_env
// HEREDOCの処理もここでやる
__attribute__((nonnull))
t_cprocinf	*init_ch_proc_info_arr(t_cmdarr *cmdarr)
{
	size_t		i;
	t_cprocinf	*arr;

	arr = malloc(cmdarr->len * sizeof(t_ch_proc_info));
	if (arr == NULL)
		return (_err_free_retnull(arr, "init_ch_proc_info_arr()/malloc"));
	i = 0;
	while (i < cmdarr->len)
	{
		arr[i] = _init_ch_proc_info(cmdarr, i);
		arr[i].fd_stdin_save = arr->fd_stdin_save;
		arr[i].fd_stdout_save = arr->fd_stdout_save;
		i++;
	}
	return (arr);
}
