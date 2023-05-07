/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfujita <kfujita@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 19:05:51 by kfujita           #+#    #+#             */
/*   Updated: 2023/05/07 19:07:12 by kfujita          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// - exit
#include <stdlib.h>

#include "_childs.h"

noreturn void	exec_command(t_ch_proc_info *info_arr, size_t index)
{
	(void)info_arr;
	(void)index;
	exit(0);
}
