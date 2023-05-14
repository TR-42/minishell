/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ch_proc_info_arr.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:43:45 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/15 00:51:02 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "childs.h"
#include "_env_util.h"

static t_cprocinf	_init_ch_proc_info(t_cmdarr *cmdarr, size_t i,
	char **envp, char **path_arr)
{
	t_cprocinf	info;

	info = (t_cprocinf){0};
	info.cmdarr = cmdarr;
	info.cmd = (t_cmdelmarr *)vect_at(cmdarr, i);
	info.path_arr = path_arr;
	info.envp = envp;
	return (info);
}

// HEREDOCの処理もここでやる
t_cprocinf	*init_ch_proc_info_arr(t_cmdarr *cmdarr, char **envp)
{
	size_t		i;
	t_cprocinf	*arr;
	char		**path_arr;

	arr = malloc(cmdarr->len * sizeof(t_ch_proc_info));
	if (arr == NULL)
		return (arr);
	path_arr = get_path_in_env(envp);
	if (path_arr == NULL)
	{
		free(arr);
		return (NULL);
	}
	i = 0;
	while (i < cmdarr->len)
	{
		arr[i] = _init_ch_proc_info(cmdarr, i, envp, path_arr);
		i++;
	}
	return (arr);
}
