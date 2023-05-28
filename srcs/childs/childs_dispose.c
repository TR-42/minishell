/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_dispose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:58:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/25 22:05:43 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "childs.h"

// !! NO_ERR
// TODO: きちんと一つ一つdisposeする
void	dispose_proc_info_arr(t_ch_proc_info *info_arr)
{
	size_t	i;

	if (info_arr == NULL)
		return ;
	i = 0;
	dispose_t_cmdarr(info_arr->cmdarr);
	if (info_arr->path_arr != NULL)
	{
		while (info_arr->path_arr[i] != NULL)
			free((void *)(info_arr->path_arr[i++]));
	}
	free(info_arr->path_arr);
	free(info_arr);
}
