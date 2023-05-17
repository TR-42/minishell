/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs_dispose.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 18:58:13 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/17 23:50:32 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "childs.h"

// TODO: きちんと一つ一つdisposeする
void	dispose_proc_info_arr(t_ch_proc_info *info_arr)
{
	size_t	i;

	if (info_arr == NULL)
		return ;
	i = 0;
	dispose_t_cmdarr(info_arr->cmdarr);
	while (info_arr->path_arr[i] != NULL)
		free((void *)(info_arr->path_arr[i++]));
	free(info_arr->path_arr);
	free(info_arr);
}
